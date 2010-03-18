/* dtkSshController.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Mar 16 14:53:39 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Mar 17 16:21:16 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 61
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkSshController.h"
#include "dtkSshLibssh.h"

#include <dtkCore/dtkGlobal.h>
#include <dtkCore/dtkLog.h>

// /////////////////////////////////////////////////////////////////
// Helper functions
// /////////////////////////////////////////////////////////////////

int authenticate_console(ssh_session session);
int authenticate_kbdint(ssh_session session);
int verify_knownhost(ssh_session session);
ssh_session connect_ssh(const char *hostname, const char *user, int verbosity);

// /////////////////////////////////////////////////////////////////
// dtkSshControllerPrivate
// /////////////////////////////////////////////////////////////////

class dtkSshControllerPrivate
{
public:
    ssh_session session;
    ssh_channel channel;
};

// /////////////////////////////////////////////////////////////////
// dtkSshController
// /////////////////////////////////////////////////////////////////

dtkSshController *dtkSshController::instance(void)
{
    if(!s_instance)
        s_instance = new dtkSshController;

    return s_instance;
}

bool dtkSshController::createConnection(const QUrl& host)
{
    d->session = connect_ssh(host.toString().toAscii().constData(), NULL, 0);

    if (d->session == NULL)
        return false;
    
    d->channel = channel_new(d->session);

    if (d->channel == NULL) {
        ssh_disconnect(d->session);
        ssh_finalize();
        return false;
    }
    
    int rc = channel_open_session(d->channel);

    if (rc < 0) {
        channel_close(d->channel);
        ssh_disconnect(d->session);
        ssh_finalize();
        return false;
    }

    return true;
}

bool dtkSshController::closeConnection(void)
{
    if(d->channel) {
        dtkDebug() << "Closing ssh channel.";
        channel_send_eof(d->channel);
        channel_close(d->channel);
    }

    if(d->session) {
        dtkDebug() << "Terminating ssh session.";
        ssh_disconnect(d->session);
        ssh_finalize();
    }

    return true;
}

bool dtkSshController::execute(const QString& command, QString& result)
{
    if (!d->session) {
        dtkWarning() << "No ssh session active. Cannot execute command.";
        return false;
    }

    if (!d->channel) {
        dtkWarning() << "No ssh channel opened. Cannot execute command.";
        return false;
    }
        
    int rc = channel_request_exec(d->channel, command.toAscii().constData());

    if (rc < 0) {
        dtkWarning() << "Failed to execute command.";
        return 1;
    }

    if (channel_is_open(d->channel)) {
        while (channel_poll(d->channel, 0) >= 0) {
            ssh_buffer buf = buffer_new();
            rc = channel_read_buffer(d->channel, buf, 0, 0);
            if (rc < 0) {
                buffer_free(buf);
                return false;
            }
            
            QString buffer = (char *)buffer_get(buf);

            if(!buffer.simplified().isEmpty())
                result.append(buffer);
            
            buffer_free(buf);
        }
    }

    result = result.trimmed();

    return true;
}

dtkSshController::dtkSshController(void) : QObject(), d(new dtkSshControllerPrivate)
{
    
}

dtkSshController::~dtkSshController(void)
{
    delete d;

    d = NULL;
}

dtkSshController *dtkSshController::s_instance = NULL;

// /////////////////////////////////////////////////////////////////
// Helper functions
// /////////////////////////////////////////////////////////////////

int authenticate_kbdint(ssh_session session)
{
    int err=ssh_userauth_kbdint(session,NULL,NULL);
    const char *name, *instruction, *prompt;
    char *ptr;
    char buffer[128];
    int i,n;
    char echo;

    while (err==SSH_AUTH_INFO){
        name=ssh_userauth_kbdint_getname(session);
        instruction=ssh_userauth_kbdint_getinstruction(session);
        n=ssh_userauth_kbdint_getnprompts(session);
        if(strlen(name)>0)
            printf("%s\n",name);
        if(strlen(instruction)>0)
            printf("%s\n",instruction);
        for(i=0;i<n;++i){
            prompt=ssh_userauth_kbdint_getprompt(session,i,&echo);
            if(echo){
                printf("%s",prompt);
                fgets(buffer,sizeof(buffer),stdin);
                buffer[sizeof(buffer)-1]=0;
                if((ptr=strchr(buffer,'\n')))
                    *ptr=0;
                if (ssh_userauth_kbdint_setanswer(session,i,buffer) < 0) {
                    return SSH_AUTH_ERROR;
                }
                memset(buffer,0,strlen(buffer));
            } else {
                ptr=getpass(prompt);
                if (ssh_userauth_kbdint_setanswer(session,i,ptr) < 0) {
                    return SSH_AUTH_ERROR;
                }
            }
        }
        err=ssh_userauth_kbdint(session,NULL,NULL);
    }

    return err;
}

int authenticate_console(ssh_session session)
{
    int rc;
    int method;
    char *password;
    char *banner;

    // Try to authenticate
    rc = ssh_userauth_none(session, NULL);

    if (rc == SSH_AUTH_ERROR) {
        perror("Authentication failed.");
        return rc;
    }

    method = ssh_auth_list(session);

    while (rc != SSH_AUTH_SUCCESS) {

        // Try to authenticate with public key first
        if (method & SSH_AUTH_METHOD_PUBLICKEY) {
            rc = ssh_userauth_autopubkey(session, NULL);
            if (rc == SSH_AUTH_ERROR) {
                perror("Authentication failed.");
                return rc;
            } else if (rc == SSH_AUTH_SUCCESS) {
                break;
            }
        }

        // Try to authenticate with keyboard interactive";
        if (method & SSH_AUTH_METHOD_INTERACTIVE) {
            rc = authenticate_kbdint(session);
            if (rc == SSH_AUTH_ERROR) {
                perror("Authentication failed.");
                return rc;
            } else if (rc == SSH_AUTH_SUCCESS) {
                break;
            }
        }

        password=getpass("Password: ");
        // Try to authenticate with password
        if (method & SSH_AUTH_METHOD_PASSWORD) {
            rc = ssh_userauth_password(session, NULL, password);
            if (rc == SSH_AUTH_ERROR) {
                perror("Authentication failed.");
                return rc;
            } else if (rc == SSH_AUTH_SUCCESS) {
                break;
            }
        }
    }

    banner = ssh_get_issue_banner(session);
    if (banner) {
        printf("%s\n",banner);
        free(banner);
    }

    return rc;
}

#include <errno.h>

int verify_knownhost(ssh_session session)
{
    char *hexa;
    int state;
    char buf[10];
    unsigned char *hash = NULL;
    int hlen;

    state=ssh_is_server_known(session);

    hlen = ssh_get_pubkey_hash(session, &hash);

    if (hlen < 0) {
        return -1;
    }

    switch(state){
    case SSH_SERVER_KNOWN_OK:
        break; /* ok */
    case SSH_SERVER_KNOWN_CHANGED:
        fprintf(stderr,"Host key for server changed : server's one is now :\n");
        ssh_print_hexa("Public key hash",hash, hlen);
        free(hash);
        fprintf(stderr,"For security reason, connection will be stopped\n");
        return -1;
    case SSH_SERVER_FOUND_OTHER:
        fprintf(stderr,"The host key for this server was not found but an other type of key exists.\n");
        fprintf(stderr,"An attacker might change the default server key to confuse your client"
                "into thinking the key does not exist\n"
                "We advise you to rerun the client with -d or -r for more safety.\n");
        return -1;
    case SSH_SERVER_FILE_NOT_FOUND:
        fprintf(stderr,"Could not find known host file. If you accept the host key here,\n");
        fprintf(stderr,"the file will be automatically created.\n");
        /* fallback to SSH_SERVER_NOT_KNOWN behavior */
    case SSH_SERVER_NOT_KNOWN:
        hexa = ssh_get_hexa(hash, hlen);
        fprintf(stderr,"The server is unknown. Do you trust the host key ?\n");
        fprintf(stderr, "Public key hash: %s\n", hexa);
        free(hexa);
        fgets(buf,sizeof(buf),stdin);
        if(strncasecmp(buf,"yes",3)!=0){
            return -1;
        }
        fprintf(stderr,"This new key will be written on disk for further usage. do you agree ?\n");
        fgets(buf,sizeof(buf),stdin);
        if(strncasecmp(buf,"yes",3)==0){
            if (ssh_write_knownhost(session) < 0) {
                free(hash);
                fprintf(stderr, "error %s\n", strerror(errno));
                return -1;
            }
        }

        break;
    case SSH_SERVER_ERROR:
        free(hash);
        fprintf(stderr,"%s",ssh_get_error(session));
        return -1;
    }

    free(hash);

    return 0;
}

ssh_session connect_ssh(const char *host, const char *user,int verbosity)
{
    ssh_session session;
    int auth=0;

    session=ssh_new();
    if (session == NULL) {
        return NULL;
    }

    if(user != NULL){
        if (ssh_options_set(session, SSH_OPTIONS_USER, user) < 0) {
            ssh_disconnect(session);
            return NULL;
        }
    }

    if (ssh_options_set(session, SSH_OPTIONS_HOST, host) < 0) {
        return NULL;
    }

    ssh_options_set(session, SSH_OPTIONS_LOG_VERBOSITY, &verbosity);

    if(ssh_connect(session)){
        fprintf(stderr,"Connection failed : %s\n",ssh_get_error(session));
        ssh_disconnect(session);
        return NULL;
    }

    if(verify_knownhost(session)<0){
        ssh_disconnect(session);
        return NULL;
    }

    auth=authenticate_console(session);

    if(auth==SSH_AUTH_SUCCESS){
        return session;
    } else if(auth==SSH_AUTH_DENIED){
        fprintf(stderr,"Authentication failed\n");
    } else {
        fprintf(stderr,"Error while authenticating : %s\n",ssh_get_error(session));
    }

    ssh_disconnect(session);

    return NULL;
}
