import Qt.labs.presentation 1.0
import QtQuick 2.3
import QtQuick.Controls 1.3

import QtMultimedia 5.3
import QtWebKit 3.0

ApplicationWindow {
    id: window
    title: "DTK Distributed"
    visible: true
    /* visibility: "FullScreen" */
    width: 1280
    height: 720

OpacityTransitionPresentation
    /* Presentation */
    {
        id: presentation
        width: parent.width
        height: parent.height

        showNotes: true
        Keys.forwardTo: [video, elapsed]
        // FIXME: how can i get QWindow::FullScreen in QML ? (using hardcoded 5 is ugly)
        Keys.onPressed: { if (event.key == Qt.Key_F11)  { (window.visibility == 5) ? window.visibility = "Windowed" : window.visibility = "FullScreen"} }
        SlideCounter {}
        Elapsed {
            id: elapsed
            duration: 15 * 60 // 15 mn
        }

        Image {
            id: background
            source: "images/Arc-Brave.png"
            opacity: 0.5
            width: parent.width
            height: parent.height
            anchors.centerIn: parent
        }

        Image {
            id: dtklogo
            source: "images/dtk-logo.png"
            opacity: 0.7
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.margins: 10
        }

        Image {
            id: inriaLogo
            mipmap: true
            source: "images/inria-transparent.png"
            width: 404 / 1.5
            height: 145 / 1.5
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.margins: 0
        }

        Slide {
            title: "DREAM-Tech - DTK Distributed"
            centeredText: "Nicolas Niclausse / Thibaud Kloczko / Julien Wintz"

        }

        Slide {
            title: "Plan"
            content: [
            "Motivations",
            "Management des ressources",
            "Application distribuées",
            "Conteneurs distribués"
            ]

        }
        Slide {
            title: "Contexte"
            textFormat: Text.RichText
            content: [
            "ADT DTK (depuis 2012) ",
            " architecture modulaire, plugins",
            " Multi Plateforme, C++, Qt",
            " num3sis, axel, medInria, enas, carbonQuant, pib, inalgae",
            "Layers:",
            " dtkCore",
            " dtkComposer",
            " dtkPlot",
            " dtkLinearAlgebraSparse",
            " <i><b>dtkDistributed</b></i>",
            ]
        }

        Slide {
           title: "Motivations"
            content: [
            "Faciliter l\'utilisation des ressources de calcul ",
            " indépendances vis à vis des gestionnaires de ressources (oar, torque, accès direct)",
            " déploiement automatique",
            "  ssh (tunnelling si besoin),  MPI_comm_spawn ",
            "Simplifier l\'écriture d\'applications distribuées (API de haut niveau)",
            "Faciliter le prototypage",
            " pas de dépendances en dur sur des bibliothèques tierces (MPI)",
            " implémentation par défaut multi plateforme (communicateur qthread)",
            "Faciliter les intéractions calcul / visualisation ",
            ]
        }

        Slide {
           title: "Historique"
            content: [
            "fin 2011: premier prototype du resource manager",
            "2012: intégration dans le composer dtk",
            "fin 2012: visu intéractive de simulation distante dans le composer num3sis",
            "2013: refonte du communicator sous forme de plugins",
            "mi 2014: vecteur et graphe distribués",
            "2015: intégration dans le layer algèbre sparse",
            ]
        }

        Slide {
            title: "Management de ressources via dtkDistributed"
            content: [
            "3 composants:",
            " 1 contrôleur: dtkDistributedController (tourne sur la machine cliente (laptop par ex.))",
            " 1 serveur dtkDistributedServer (tourne sur la frontale du cluster), qui instancie un ressource manager",
            "  OAR",
            "  Torque",
            "  SSH",
            " N slaves dtkDistributedSlave (exécution sur un/des noeuds d\'un cluster)",
            ]
            notes: "Le controlleur et le serveur sont optionnels, on peut lancer aussi une application distribuées manuellement sur le cluster ou via kali"
        }
        Slide {
            title: "Management de ressources via dtkDistributed"
            Rectangle {
                width:  parent.width * 0.8
                height: parent.height
                anchors.centerIn: parent
                opacity: 0.9
                color : "black"
                radius: 10
                Image {
                width:  parent.width
                height: parent.height
                    id: dtkdistributed
                    source: "images/distributed.png"
                    /* mipmap: true */
                    anchors.margins: 10
                }
            }
        }

        Slide {
            title: "Management de ressources via dtkDistributed"
            content: [
            "Exemple: Dashboard QML",
            " Object dtkDistributedControlleur instancié en QML",
            " Serveur sur la frontale choisie",
            " Lance un job Slave via le serveur",
            ]
        }




        Slide {
            id: interactiveSlide
            title: "DTK Distributed Dashboard"

            /* Background { */
            /*     id: backgroundb */
            /* } */

            Background {
                id: backgroundb
            }

            Dashboard {
                id: dashboard
            }
        }

        Slide {
            title: "Application distribuées"
            content: [
            "distributed application",
            "communicator",
            "policy",
            "settings",
            ]

        }

        Slide {
            title: "Example de slave"

            CodeSection {
                text: "int main(int argc, char **argv)
 {
   dtkDistributedAbstractApplication *app = dtkDistributed::create(argc, argv);

   QCommandLineParser *parser = app->parser();
   parser->setApplicationDescription(\"DTK distributed slave example application.\");
   QCommandLineOption serverOption(\"server\", \"DTK distributed server URL\", \"URL\");
   parser->addOption(serverOption);

   app->initialize();
   if (!parser->isSet(serverOption)) {
     qCritical() << \"Error: no server set ! Use --server <url> \" ;
     return 1;
   }
   slaveWork work;
   work.server = parser->value(serverOption);
   app->spawn();
   app->exec(&work);
   app->unspawn();

   return 0;
}"
            }
        }


        Slide {
            title: "Example de slave (suite) "

        CodeSection {
            text: "class slaveWork : public QRunnable {
 public:
   QString server;

 public:
  void run(void) {
     dtkDistributedCommunicator *comm = dtkDistributed::communicator::instance();
     dtkDistributedSlave slave;

     slave.connectFromJob(server);
     QThread::sleep(5);
     if (comm->rank() == 0) {
         QString hello = \"I'm the master slave, we are \" + QString::number(comm->size())+ \" slaves\";
         QVariant v(hello);
         dtkDistributedMessage msg(dtkDistributedMessage::DATA,slave.jobId(),
                                   dtkDistributedMessage::CONTROLLER_RANK, v);

         msg.send(slave.socket());
     }
     QThread::sleep(5);
     slave.disconnectFromJob(server);
    }
};"
        }
        }

/* ' */


        Slide {
            title: "Controlleur intégré dans numComposer"

            Rectangle {
                id: videorect
                width:  height * 1.59
                height: parent.height
                anchors.centerIn: parent
                /* border.color : "black" */
                color: "transparent"

                Video {
                    id: video
                    width:  parent.width
                    height: parent.height-8

                    anchors.top: parent.top
                    anchors.left: parent.left
                    source: "http://num3sis.inria.fr/blog/wp-content/uploads/sampling-aero-nef.mp4"
                    /* source: "file:///tmp/sampling-aero-nef.mp4" */
                    autoPlay: false
                    Keys.onSpacePressed: {
                        video.playbackState == MediaPlayer.PlayingState ? video.pause() : video.play()
                        event.accepted = true;
                    }
                    Keys.onDownPressed: video.seek(video.position - 5000)
                    Keys.onUpPressed: video.seek(video.position + 5000)
                }
                ProgressBar {
                    width:  parent.width
                    anchors.bottom: parent.bottom
                    height:  8
                    value: video.position/ video.duration
                }
            }
        }

        Slide {
            title: "Conteneurs distribués"
            content: [
            "container",
            "mapper",
            "array",
            "buffer manager",
            "cache",
            "navigator, iterator"
            ]

        }

        Slide {
            title: "Algèbre Linéaire Creuse"
            content: [
            "dtkDistributedSparseMatrix",
            "dtkLinearSolverSparse",
            ]

        }

         Slide {
             title: "API documentation"
             ScrollView {
                 height: parent.height
                 width:  parent.width
                 WebView {
                     id: webview
                     url: "http://dtk-legacy.inria.fr/docs"
                     anchors.fill: parent
                     onNavigationRequested: {
                         // detect URL scheme prefix, most likely an external link
                         var schemaRE = /^\w+:/;
                         if (schemaRE.test(request.url)) {
                             request.action = WebView.AcceptRequest;
                         } else {
                             request.action = WebView.IgnoreRequest;
                             // delegate request.url here
                         }
                     }
                 }
             }
         }

        Slide {
            title: "Contacts"
            centeredText: "dtk-team@inria.fr"
        }
     }
}


/* dtkDistributed introduit un certain nombre de conteneurs (Array, Graph) qui ont vocation à masquer à l’utilisateur le recours explicite à des procédures de communication entre les processus. */
/* Le but étant de donner à l’utilisateur, autant que possible, la possibilité de programmer “comme en séquentiel”: */
