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
            duration: 90 * 60 // 90 mn
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
            width: 404 / 1.7
            height: 145 / 1.7
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.margins: 0
        }

        Slide {
            title: "DREAMtech - DTK Distributed"
            centeredText: "Nicolas Niclausse / Thibaud Kloczko / Julien Wintz"

        }

        Slide {
            title: "Plan"
            content: [
            "Contexte & Motivations",
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
            " méta plateforme, pour développer des plateformes modulaires (plugins)",
            " multi Plateforme, C++, Qt",
            " num3sis, axel, medInria, enas, carbonQuant, pib, inalgae, bolis, winpos",
            "layers DTK:",
            " dtkCore",
            " dtkComposer",
            " dtkPlot",
            " dtkLinearAlgebraSparse",
            " <i><b>dtkDistributed</b></i>",
            ]
        }

        Slide {
           title: "dtkDistributed: Motivations"
            content: [
            "Faciliter l\'utilisation des ressources de calcul dans le code",
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
           title: "dtkDistributed: Historique"
            content: [
            "fin 2011: premier prototype du resource manager",
            "2012: communicateur v0, intégration dans le composer dtk",
            "fin 2012: visu intéractive de simulation distante dans le composer num3sis",
            "2013: refonte du communicator sous forme de plugins",
            "mi 2014: vecteur et graphe distribués",
            "2015: intégration dans le layer algèbre sparse",
            ]
        }

        Slide {
            title: "Management de ressources via dtkDistributed"
            textFormat: Text.RichText
            content: [
            "3 composants:",
            " 1 contrôleur: <b>dtkDistributedController</b> (sur la machine cliente (laptop par ex.))",
            " 1 serveur <b>dtkDistributedServer</b> (sur la frontale du cluster), qui instancie un ressource manager",
            "  OAR",
            "  Torque",
            "  SSH",
            " N slaves <b>dtkDistributedSlave</b> (sur un(des) noeud(s) d\'un cluster)",
            ]
            notes: "Le contrôleur et le serveur sont optionnels, on peut lancer aussi une application distribuées manuellement sur le cluster ou via kali"
        }
        Slide {
            title: "Management de ressources via dtkDistributed"
            Rectangle {
                width:  parent.width * 0.6
                height: parent.height
                anchors.centerIn: parent
                //opacity: 0.0
                color : "lightgrey"
                radius: 10
                Image {
                    width:  parent.width
                    height: parent.height
                    id: dtkdistributed
                    source: "images/dtkDistributed_controller.png"
                    /* mipmap: true */
                    anchors.margins: 10
                }
            }
        }


        Slide {
            title: "Application distribuées"
            content: [
            "Communicator",
            "Messages",
            "Policy, Settings",
            "Distributed application",
            ]

        }

        Slide {
            title: "Communicator"
            content: [
            "dtkDistributedCommunicator",
            " interface pour le calcul parallèle",
            " paradigme de programmation inspiré de MPI",
            " inclus des primitives de:",
            "  déploiement",
            "  communication",
            "  synchronisation"
            ]
        }
        Slide {
            title: "Communicator"
            content: [
            "implémenté sour forme de plugins",
            " qthread (par défaut)",
            " MPI",
            " MPI3",
            "primitives de communication",
            " send/receive/ireceive/broadcast/reduce",
            " barrier/wait",
            "buffers distribués",
            " get/put/accumulate",
            ]
        }
        Slide {
            title: "Communicator: sérialisation"
            content: [
            "primitives de communications compatibles avec:",
            " tableau de type simple",
            " QVariant",
            "sérialisation via le QVariant: ",
            ]
            CodeSection {
                height: parent.height * 0.45
                anchors.bottom: parent.bottom
                text: 'Q_DECLARE_METATYPE(monType)
qRegisterMetaTypeStreamOperators<monType>("monType");
qRegisterMetaTypeStreamOperators<monType*>("monType*");

// handle the pointer version of qdatastream operators << and >>
#include <dtkMeta/dtkMeta.h>;

QDataStream& operator<<(QDataStream& s, const monType& data);
QDataStream& operator>>(QDataStream& s, monType& data);'
            }
        }

        CodeSlide {
            title: "Communicator: sérialisation"
            code:'// rank 0 is sending each slave it\'s mesh

if (d->communicator->rank() == 0) {
  dtkContainerVector<numMesh*> *meshes = d->partitioner->meshes();
  for(qlonglong i = 1; i < meshes->count(); ++i) {
     QVariant v = QVariant::fromValue(meshes->at(i));
     d->communicator->send(v, i, tagSend);
     delete meshes->at(i);
  }
} else {
  // each slave received it\'s mesh
  QVariant v;
  d->communicator->receive(v, 0, tagSend);
  d->mesh = v.value<numMesh*>();
}'
        }
        CodeSlide {
            title: "Communicator: sérialisation, vraie version"
            code:'// rank 0 is sending each slave it\'s mesh

if (d->communicator->rank() == 0) {
  dtkContainerVector<numMesh*> *meshes = d->partitioner->meshes();
  for(qlonglong i = 1; i < meshes->count(); ++i) {
     d->communicator->send(meshes->at(i), i, tagSend);
     delete meshes->at(i);
  }
} else {
  // each slave received it\'s mesh
  d->communicator->receive(d->mesh, 0, tagSend);
}
'
        }

        Slide {
            title: "Communicator: spawn"
            textFormat: Text.RichText
            content: [
            "déploiement du communicateur: <code>spawn()</code>",
            " <i>qthread</i> : instanciation d\'une pool de thread (QThreadPool)",
            " <i>mpi</i> : <code>MPI_Comm_Spawn</code>",
            "  Pas besoin de mpirun (avec openmpi)",
            "exécution du code parallèle: <code>exec(QRunnable)</code>",
            " QRunnable: méthode virtuelle <code>run()</code> à implémenter",
            ]
        }

        Slide {
            title: "Messages"
            textFormat: Text.RichText
            content: [
            "échange de messages entre contrôleur, serveur et slave",
            "protocole basé sur JSON et du pseudo HTTP",
            "interface C++: <code>dtkDistributedMessage</code>",
            " Plusieurs méthodes:",
            "  STATUS: demande d\'état du cluster",
            "  OKSTATUS: état du cluster",
            "  NEWJOB: création d\'un job",
            "  DELJOB: suppression d\'un job",
            "  DATA: échange de données (QVariant)",
            "  ...",
            ]
        }

        Slide {
            title: "Policy & Settings"
            content: [
            "policy:",
            " permet de choisir l\'implémentation (qthread, mpi, mpi3)",
            " permet de spécifier les machines sur lequel l\'application tourne",
            "  s\'interface avec Torque, OAR",
            "  variable d\'environnement DTK_NUM_PROCS",
            "Settings:",
            " fichier ini",
            "  défini vers le plugins path",
            "  autres options ...",
            ]
        }

        Slide {
            title: "dtkDistributedApplication"
            textFormat: Text.RichText
            content: [
            "simplifie l\'invocation d\'une application",
            " configure automatiquement la policy",
            " initialise le plugin manager du communicator",
            "options en ligne de commande",
            " nombre de procs, policy, etc.",
            " ajout d\'option spécifiques.",
            "déploiement de l\'application (<code>spawn</code>)",
            "exécution des taches de calcul (<code>exec</code>)"
            ]
            CodeSection {
                width: parent.width / 2.4
                anchors.right: parent.right
                text:'dtkDistributed::create(argc,argv);

QCommandLineParser *parser=app->parser();

app.initialize();

app.spawn();

app.exec(work);

app.unspawn();
'
            }
        }

        Slide {
            title: "Distributed application"
            CodeSection {

                text: '# myappli --help
Usage: myappli [options]
Lorem ipsum dolor sit amet, consectetur adipiscing elit
Options:
  --myoption <foo|bar>                            myappli option(s)

  --policy <qthread|mpi|mpi3>                     dtkDistributed policy
                                                  (default is qthread)
  --np <int>                                      number of processes
  --hosts <hostname>                              hosts (multiple hosts can be specified)
  -h, --help                                      Displays this help.
  -v, --version                                   Displays version information.
  --settings <filename>                           settings file
  --verbose                                       verbose plugin initialization
  --nw, --no-window                               non GUI application (no window)
  --loglevel <trace|debug|info|warn|error|fatal>  log level used by dtkLog
                                                  (default is info)
  --logfile <filename | console>                  log file used by dtkLog; default is:
                                                  /home/nniclaus/.local/share/inria/dtk
                                                  DistributedSlave/dtkDistributedSlave.log'
            }
        }

        CodeSlide {
            title: "Example de slave"
            code: 'int main(int argc, char **argv) {
   dtkDistributedAbstractApplication *app=dtkDistributed::create(argc,argv);
   QCommandLineParser *parser = app->parser();
   parser->setApplicationDescription("DTK distributed slave application.");
   QCommandLineOption serverOption("server", "Server URL", "URL");
   parser->addOption(serverOption);
   app->initialize();
   if (!parser->isSet(serverOption)) {
     qCritical() << "Error: no server set ! Use --server <url> " ;
     return 1;
   }
   slaveWork work;
   work.server = parser->value(serverOption);
   app->spawn();
   app->exec(&work);
   app->unspawn();
   return 0;
}'
        }

        CodeSlide {
            title: "Example de slave (suite) "
            code: 'class slaveWork : public QRunnable {
 public:
   QString server;
 public:
  void run(void) {
     dtkDistributedCommunicator *c=dtkDistributed::communicator::instance();
     dtkDistributedSlave slave;
     slave.connectFromJob(server);
     QThread::sleep(5);
     if (c->rank() == 0) {
         QString s = QString::number(c->size());
         QString hello = "I\'m the master slave, we are "+s+" slaves";
         QVariant v(hello);
         dtkDistributedMessage m(dtkDistributedMessage::DATA,slave.jobId(),
                                 dtkDistributedMessage::CONTROLLER_RANK, v);
         m.send(slave.socket());
     }
     QThread::sleep(5); slave.disconnectFromJob(server); }};'
        }

        Slide {
            title: "Examples d\'application avec contrôleur/slave"
            content: [
            "Dashboard QML",
            " Objet 'dtkDistributedController' instancié en QML",
            " Serveur sur la frontale choisie",
            " Lance un job Slave via le serveur",
            " Affiche les données envoyées par le slave",
            ]
        }

        Slide {
            id: dashboardSlide
            title: "DTK Distributed Dashboard"

            Background {
                id: backgroundb
            }

            Dashboard {
                id: dashboard
                path: workingDirectory
            }
        }

        Slide {
            title: "Contrôleur intégré dans numComposer"

            Rectangle {
                id: videorect
                width:  height * 1.59
                height: parent.height
                anchors.centerIn: parent
                border.color : "black"
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
                    id: slider
                    width:  parent.width
                    height:  8
                    anchors.left: parent.left
                    anchors.bottom: parent.bottom
                    value: video.position/ video.duration
                }
            }
        }

        Slide {
            title: "Conteneurs distribués"
            content: [
            "étude d'un cas a priori simple",
            "état de l'art",
            "organisation des classes",
            "dtkDistributedArray",
            "dtkDistributedGraphTopology",
            "retour sur le cas initial."
            ]

        }

        Slide {
            title: "Calcul de maximum sur un graphe"
            Rectangle {
                width:  parent.width * 0.8
                height: parent.height
                anchors.centerIn: parent
                //opacity: 0.0
                color : "lightgrey"
                radius: 10
                Image {
                width:  parent.width
                height: parent.height
                    id: graph_sequential
                    source: "images/graph.png"
                    /* mipmap: true */
                    anchors.margins: 10
                }
            }
        }

        Slide {
            title: "Calcul de maximum sur un graphe"
            CodeSection {
                anchors.top: parent.top
                height : parent.height * 0.25
                text: 'Foreach vertex in graph {
   Foreach neighbour of vertex {
       max_values[vertex_id] = Max(max_values[vertex_id], values[neighbour_id]);
   }
}'
            }
            content: [
            "","",
            "Structure de graphe simple",
            "Algorithme simple"
            ]
        }

        Slide {
            title: "Calcul de maximum sur un graphe distribué"
            Rectangle {
                width:  parent.width * 0.8
                height: parent.height
                anchors.centerIn: parent
                //opacity: 0.0
                color : "lightgrey"
                radius: 10
                Image {
                width:  parent.width
                height: parent.height
                    id: graph_part
                    source: "images/graph_part.png"
                    /* mipmap: true */
                    anchors.margins: 10
                }
            }
        }

        Slide {
            title: "Calcul de maximum sur un graphe distribué"
            CodeSection {
                anchors.top: parent.top
                height : parent.height * 0.75
                text:
'// Local Computation
Foreach vertex in subGraph {
    Foreach neighbour of vertex {
        max_values[vertex_id] = Max(max_values[vertex_id], values[neighbour_id]);
    }

// Boundary computation
Foreach boundary in subGraph {
    Foreach vertex of Boundary {
        local_max_values[local_id] = max_values[vertex_id];
    }
    Send(local_max_values);

    Receive(extern_max_values);
    Foreach vertex of Boundary {
        max_values[vertex_id] = Max(max_values[vertex_id], extern_max_values[ext_id]);
    }
}'
            }
            content: [
            "","","","","",
            "Complexité accrue en terme de structure et d'algorithme"
            ]
        }

        Slide {
            title: "Calcul du maximum sur les voisins des voisins"
            content: [
            ":-/",
            "Refaire les structures",
            "Repenser l'algorithmie",
            "...",
            "Tout compte fait, on va s\'en passer..."
            ]
        }

        Slide {
            title: "Bibliothèques existantes"
            content: [
            "Parallel Standard Library (PSTL) -> plus maintenu",
            "Intel Threadings Building Blocks (TBB) -> seulement multithread",
            "Parallel Object-Oriented Methods and Applications (POOMA) -> pas de structure de graphe",
            "Standard Template Adaptive Parallel Library (STAPL) -> ni sources ni binaires",
            "Fortran Coarray (OpenCorrays) -> code C qui génère du Fortran!"
            ]
        }

        Slide {
            title: "dtkDistributed Containers"
            // Rectangle {
            //     width:  parent.width
            //     height: parent.height
            //     anchors.centerIn: parent
            //     opacity: 0.8
            //     color : "lightgrey"
            //     radius: 10
                Image {
                anchors.centerIn: parent
                width:  parent.width * 0.9
                height: parent.height
                    id: dtkDistributedContainers
                    source: "images/dtkDistributed.png"
                    /* mipmap: true */
                    anchors.margins: 10
                }
            //}
        }

        CodeSlide {
            title: "dtkDistributedArray : API"
            code:
'template < typename T > class dtkDistributedArray : 
                                     public dtkDistributedContainer {
public:
  dtkDistributedArray(const qlonglong& size, dtkDistributedMapper *mapper);
 ~dtkDistributedArray(void);
public:
  bool empty(void) const;
  qlonglong size(void) const;
  void fill(const T& value);
  void setAt(const qlonglong& index, const T& value);
  T at(const qlonglong& index) const;
  T operator[](const qlonglong& index) const;
public:
  iterator  begin(void);
  iterator    end(void);
  const T *data(void) const;
        T *data(void);'
        }

        CodeSlide {
            title: "dtkDistributedArray : Sequential initialization" 
            code:
'qlonglong N = 16257;
dtkDistributedCommunicator *comm = dtkDistributed::communicator::instance();
qlonglong *input = new qlonglong[N];
for (int i = 0; i < N; ++i) {
    input[i] = i;
}
dtkDistributedArray<qlonglong> array(N);
if (comm->wid() == 0) {
    for (int j = 0; j < N; ++j) {
        array.setAt(j, input[j]);
    }
    for (int j = 0; j < N; ++j) {
        if(array.at(j) != input[j]) {
            return false;
        }
    }
}
comm->barrier();'
        }

        CodeSlide {
            title: "dtkDistributedArray : Parallel initialization"
            code:
'qlonglong N = 16257;
dtkDistributedCommunicator *comm = dtkDistributed::communicator::instance();
qlonglong *input = new qlonglong[N];
for (int i = 0; i < N; ++i) {
    input[i] = i;
}

dtkDistributedArray<qlonglong> array(N);

dtkDistributedArray<qlonglong>::iterator ite = array.begin();
dtkDistributedArray<qlonglong>::iterator end = array.end();

for(int i = 0; ite != end; ++ite, ++i) {
    *ite = input[array.mapper()->localToGlobal(i, comm->wid())]);
}
comm->barrier();'
        }

        Slide {
            title: "dtkDistributedArray : globale vs locale"
            CodeSection {
                id : globaleapi
                width:  parent.width * 0.475
                height: parent.height * 0.5
                anchors {
                    left: parent.left
                    verticalCenter: parent.verticalCenter
                }
                gradient: Gradient {
                    GradientStop { position: 0; color: Qt.rgba(0.9, 0.9, 0.9, 0.5); }
                    GradientStop { position: 1; color: Qt.rgba(0.6, 0.6, 0.6, 0.5); }
                }
                border.color: parent.textColor;
                antialiasing: true
                text:
'
bool empty(void) const;
qlonglong size(void) const;

void fill(const T& value);

void setAt(const qlonglong& id, const T& val);

T at(const qlonglong& id) const;
T operator[](const qlonglong& id) const;'
            }
            
            CodeSection {
                width:  parent.width * 0.475
                height: parent.height * 0.5
                anchors {
                    right: parent.right
                    verticalCenter: parent.verticalCenter
                }
                gradient: Gradient {
                    GradientStop { position: 0; color: Qt.rgba(0.9, 0.9, 0.9, 0.5); }
                    GradientStop { position: 1; color: Qt.rgba(0.6, 0.6, 0.6, 0.5); }
                }
                border.color: parent.textColor;
                antialiasing: true
                text:
'


iterator  begin(void);
iterator    end(void);

const T *data(void) const;
      T *data(void);'
            }
        }

        Slide {
            title: "dtkDistributedArray : architecture"
            CodeSection {
                id: array_top
                width:  parent.width
                height: parent.height * 0.35
                anchors.top: parent.top
                anchors.horizontalCenter: parent.horizontalCenter
                gradient: Gradient {
                    GradientStop { position: 0; color: Qt.rgba(0.9, 0.9, 0.9, 0.5); }
                    GradientStop { position: 1; color: Qt.rgba(0.6, 0.6, 0.6, 0.5); }
                }
                border.color: parent.textColor;
                antialiasing: true
                text:
'// all processes duplicate the mapper

dtkDistributedCommunicator *comm;

dtkDistributedMapper *mapper;'
            }
            CodeSection {
                id: array_left
                width:  parent.width * 0.3
                height: parent.height * 0.5
                anchors.top: array_top.bottom
                anchors.left: parent.left
                anchors.topMargin: parent.height * 0.1
                gradient: Gradient {
                    GradientStop { position: 0; color: Qt.rgba(0.9, 0.9, 0.9, 0.5); }
                    GradientStop { position: 1; color: Qt.rgba(0.6, 0.6, 0.6, 0.5); }
                }
                border.color: parent.textColor;
                antialiasing: true
                text:
'// unit process #0

dtkArrayData *data;

dtkDSBufferManager *bm;

dtkDSArrayCache *cache;'
            }
            CodeSection {
                id: array_center
                width:  parent.width * 0.3
                height: parent.height * 0.5
                anchors.top: array_top.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.topMargin: parent.height * 0.1
                gradient: Gradient {
                    GradientStop { position: 0; color: Qt.rgba(0.9, 0.9, 0.9, 0.5); }
                    GradientStop { position: 1; color: Qt.rgba(0.6, 0.6, 0.6, 0.5); }
                }
                border.color: parent.textColor;
                antialiasing: true
                text:
'// unit process #1

dtkArrayData *data;

dtkDSBufferManager *bm;

dtkDSArrayCache *cache;'
            }
            CodeSection {
                id: array_right
                width:  parent.width * 0.3
                height: parent.height * 0.5
                anchors.top: array_top.bottom
                anchors.right: parent.right
                anchors.topMargin: parent.height * 0.1
                gradient: Gradient {
                    GradientStop { position: 0; color: Qt.rgba(0.9, 0.9, 0.9, 0.5); }
                    GradientStop { position: 1; color: Qt.rgba(0.6, 0.6, 0.6, 0.5); }
                }
                border.color: parent.textColor;
                antialiasing: true
                text:
'// unit process #2

dtkArrayData *data;

dtkDSBufferManager *bm;

dtkDSArrayCache *cache;'
            }
        }

        CodeSlide {
            title: "dtkDistributedArray : allocation mémoire"
            code:
'template <typename T> inline void dtkDistributedArray<T>::allocate(void) 
{
    // Communicator creates the buffer manager matching its
    // implementation (Qthread, MPI, MPI3)

    bm = comm->createBufferManager();

    // Buffer manager allocates the memory according to size given by
    // the mapper

    void *local_buffer = bm->allocate<T>(mapper->localSize());

    // This buffer initializes the local container

    data = dtkArrayData<T>::fromRawData(buffer, mapper->localSize());
}'
        }

        CodeSlide {
            title: "dtkDistributedArray : accès aux valeurs"
            code:
'template <typename T> inline T dtkDistributedArray<T>::at(qlonglong id) const
{
    // Identifies the unit process that has the value
    qint32 owner = mapper->owner(id);
    // Identifies the local position of the value on the owner
    qlonglong pos = id - mapper->firstId(owner);

    // If the owner is the local process the access is direct    
    if (this->wid() == owner) {
        return data[pos];
    // Else the remote value is asked by the buffer manager
    } else {
        T val;
        bm->get(owner, pos, &val);
        return val;
    }
}'
        }

        CodeSlide {
            title: "Buffer Manager : accès aux valeurs en Qthread"
            height: parent.height * 0.55
            content: ["","","","","","Accès direct au buffer cible"]
            code:
'void qthDistributedBufferManager::get(qint32 owner, qlonglong pos, 
                                                     void *array,
                                                     qlonglong nelement = 1)
{
    // Owner id enables to get the right shared buffer

    char *buffer = d->buffers[owner];


    // Copy into array is done from pos to pos + nelement

    memcpy(array, buffer + pos * d->object_size, d->object_size * nelement);
}'
        }

        CodeSlide {
            title: "Buffer Manager : accès aux valeurs en MPI"
            height: parent.height * 0.4
            code:
'void mpiDistributedBufferManager::get(qint32 owner, qlonglong pos, 
                                       void *array, qlonglong nelement = 1)
{
    // Size of the memory to get
    qlonglong array_size = d->object_size * nelements;

    // Copy into array from the memory of the owner at position pos
    MPI_Get(array, array_size, MPI_BYTE, 
            owner, pos, array_size, MPI_BYTE, d->win);
}'
            textFormat: Text.RichText
            content: [
            "","","","",
            "Utilisation de MPI One-Sided Communication",
            " permet à un processus d'accéder à un espace d'adresse d'un autre processus sans la participation explicite de celui-ci.",
            " permet de simplifier le programme et de coder comme en mémoire partagée"
            ]
        }

        Slide {
            title: "MPI One-Sided Communication"
            textFormat: Text.RichText
            content: [
            "<code>MPI_Win_Create</code>",
            " crée une fenêtre pour l'accès par d'autres processus à une zone mémoire",
            "<code>MPI_Win_Free</code>",
            " détruit la fenêtre",
            "<code>MPI_Get / MPI_Put</code>",
            " lecture/écriture asynchrone sur une zone mémoire exposée par une fenêtre",
            "Bibliothèques utilisant MPI One-Sided Communication :",
            " <em>OpenCoarrays</em> pour les Coarrays en Fortran 2008",
            " <em>OpenShmem</em> implémentation de PGAS (Partitioned Global Address Space)"
            ]
        }

        CodeSlide {
            title: "dtkDistributedGraphTopology : API"
            code:
'class dtkDistributedGraphTopology : public dtkDistributedContainer
{
public:
  dtkDistributedArray(qlonglong vertex_count, dtkDistributedMapper *mapper);
 ~dtkDistributedArray(void);

  void addEdge(qlonglong from, qlonglong to, bool oriented = false);
  void build(void);

  qlonglong vertexCount(void) const;
  qlonglong   edgeCount(void) const;

  qlonglong neighbourCount(qlonglong vertex_id) const;
  Neighbours operator[](qlonglong vertex_id) const;

  iterator begin(void) const;
  iterator   end(void) const;
};'
        }

        CodeSlide {
            title: "dtkDistributedGraphTopology : Construction"
            height: parent.height * 0.4
            textFormat: Text.RichText
            content: ["","","","","Structure type ParCSR mais avec des dtkDistributedArray",
            " <code>Vertex_to_FirstEdge</code> : index de la première arête de chaque sommet",
            " <code>Edge_to_Vertex</code> : index du sommet cible de chaque arête"]
            code:
'dtkDistributedGraphTopology graph(18);

// Add edges into provisionnal local data structure of the graph
graph.addEdge(0, 1);
graph.addEdge(1, 2);
...
graph.addEdge(16, 17);

// Build the true structures of the graph
graph.build();'
        }

        CodeSlide {
            title: "dtkDistributedGraphTopology : API globale"
            height: parent.height * 0.56
            textFormat: Text.RichText
            content: ["","","","","","<code>dtkDistributedNavigator</code> interroge le graphe via l'API globale.",]
            code:
'typedef dtkDistributedNavigator<dtkDistributedArray<qlonglong> > Neighbours;

// Gets a navigator for neighbours of a vertex
Neighbours n = graph[i];
qlonglong n_count = n.size();

// Can iterate over all the neighbours of the vertex
Neighbours::iterator nit  = n.begin();
Neighbours::iterator nend = n.end();

for(; nit != nend; ++nit) {
    // Access to id of each neighbour
    qDebug() << *nit;
}'
        }

        CodeSlide {
            title: "dtkDistributedGraphTopology : API locale"
            height: parent.height * 0.4
            textFormat: Text.RichText
            content: ["","","","","En combinant <code>iterator</code> local et <code>navigator</code> global, on peut:",
            " accéder aux sommets voisins non-locaux",
            " accéder aux voisins des voisins non-locaux",
            " accéder aux voisins des voisins non-locaux des voisins non-locaux ;-)"]
            code:
'typedef dtkDistributedIterator<dtkDistributedGraphTopology > iterator;

// Iterates over all local vertices
iterator vit  = graph.begin();
iterator vend = graph.end();

for(; vit != vend; ++vit) {
    // Access to all the neighbours of the local vertex
    Neighbours n = *vit;
}'
        }

        CodeSlide {
            title: "Calcul du maximum sur les voisins des voisins"
            code:
'dtkDistributedGraphTopology::iterator it  = graph.begin();
dtkDistributedGraphTopology::iterator end = graph.end();

for(;it != end; ++it) {
    dtkDistributedGraphTopology::Neighbours n = *it;
    dtkDistributedGraphTopology::Neighbours::iterator nit  = n.begin();
    dtkDistributedGraphTopology::Neighbours::iterator nend = n.end();

    for(;nit != nend; ++nit) {
        dtkDistributedGraphTopology::Neighbours nn = graph[*nit];
        dtkDistributedGraphTopology::Neighbours::iterator nnit  = nn.begin();
        dtkDistributedGraphTopology::Neighbours::iterator nnend = nn.end();

        for(;nnit != nnend; ++nnit) {
            max_values[it.id()] = qMax(max_values[it.id()], values[*nnit]);
        }
    }
}'
        }

        Slide {
            title: "En résumé, ..."
            textFormat: Text.RichText
            content: [
            "Avec :",
            " une structure fondamentale :",
            "  <code>dtkDistributedArray</code>",
            " une structure aggrégatrice :",
            "  <code>dtkDistributedGraphTopology</code>",
            " et des structures périphériques d'accès :",
            "  <code>dtkDistributedIterator</code>",
            "  <code>dtkDistributedNavigator</code>",
            "le code utilisateur parallèle s'écrit comme en séquentiel",
            "YES, WE CAN !"]
        }

        Slide {
            title: "Algèbre Linéaire Creuse"
            content: [
            "dtkDistributedSparseMatrix",
            "dtkLinearSolverSparse"
            ]

        }
        Slide {
            title: "dtkSparseMatrix"
            textFormat: Text.RichText
            content: [
            "<code>dtkSparseMatrix</code>: Abstraction de Sparse Matrix",
            " itérateur de lignes: <br><code>dtkSparseMatrixLine dtkSparseMatrix::begin()/end()</code>",
            " itérateur sur les éléments de lignes:<br><code>dtkSparseMatrixLineElement dtkSparseMatrixLine::begin()/end()</code>",
            "<code>dtkSparseMatrixData:</code> implémentation séquentielle",
            "<code>dtkDistributedSparseMatrixData:</code> implémentation parallèle:",
            " <code>dtkDistributedGraphTopology</code>",
            " <code>dtkDistributedArray</code> (valeurs)",
            ]
        }

            CodeSlide {
                title: "dtkSparseMatrix"
                code: 'dtkSparseMatrixLine<double> line_it = mat.begin();
dtkSparseMatrixLine<double> line_end = mat.end();

for (; line_it != line_end; ++line_it) {
    dtkSparseMatrixLineElement<double> elt_it  = line_it.begin();
    dtkSparseMatrixLineElement<double> elt_end = line_it.end();
    qlonglong i = line_it.id();
    for(;elt_it != elt_end; ++elt_it) {
        qlonglong j = elt_it.id();
        // accès à value via l\'iterateur:
        value =  (*elt_it);
        // modification via i,j (numérotation globale)
        mat(i,j) += coef;
        // en MPI, \'+=\' implémenté via MPI_Accumulate()
    }
}
'
        }
        Slide {
            title: "dtkSparseSolver"
            content: [
            "API générique (séquentielle/parallèle)",
            "implémentations sous forme de plugins",
            " dtkSparseSolverJacobi (générique)",
            " hypreDistributedSparseSolver",
            "  utilisation de la dtkDistributedSparseMatrixData",
            "  accès direct aux buffers locaux ",
            " à venir: mumps, MaPHyS, ...",
            ]
        }

        CodeSlide {
            title: "dtkSparseSolver<T> API"
            code:'template < typename T > class dtkSparseSolver : public QRunnable
{
public:
             dtkSparseSolver(void) {;}
    virtual ~dtkSparseSolver(void) {;}

public:
  virtual void setMatrix(dtkSparseMatrix<T> *matrix) = 0;
  virtual void setRHSVector(dtkVector<T> *rhs_vector) = 0;
  virtual void setSolutionVector(dtkVector<T> *sol_vector) = 0;

  virtual void setOptionalParameters(const QHash<QString,int>& parameters);
  virtual void setOptionalParameters(const QHash<QString,double>& parameters);

public:
    virtual void run(void) = 0;
public:
    virtual dtkVector<T> *solutionVector(void) const = 0;'
        }

        CodeSlide {
            title: "dtkSparseSolverJacobi: implémentation générique"
            code: 'while(!stop_criterion) {
    line_it = mat.begin(); line_end = mat.end(); tmp=sol; d->variation=0;
    for (; line_it != line_end; ++line_it) {
        dtkSparseMatrixLineElement<double> elt_it  = line_it.begin();
        dtkSparseMatrixLineElement<double> elt_end = line_it.end();
        neighbour = 0; diag = 0; qlonglong i = line_it.id();
        for(;elt_it != elt_end; ++elt_it) {
            qlonglong j = elt_it.id();
            if (j != i) { neighbour += (*elt_it) * tmp[j];}
            else        { diag = (*elt_it); }}
        sol[i] = (rhs.at(i) - neighbour) / diag ;}
    tmp -= sol;
    d->variation = tmp.asum();
    if(iteration_count == 0) { variation_ini = d->variation;}
    if(iteration_count == d->number_of_iterations ||
         d->variation/variation_ini < d->residual_reduction_order)
         stop_criterion = true;
    ++iteration_count;  sol.clearCache(); tmp.clearCache();}'
        }
        Slide {
            title: "dtkSparseMatrixSolverApp"
            CodeSection {
                text: '>./bin/dtkSparseMatrixSolverApp --help
Usage: ./bin/dtkSparseMatrixSolverApp [options]
DTK sparse matrix solver.
Options:
  --matrix <file>                                 matrix (matrixmarket format)
  --rhs <file>                                    rhs vector (matrixmarket format)
  --sol <file>                                    solution vector to be written
  --refsol <file>                                 reference solution
  --impl <sequential|distributed>                 implementation
  --solver <jacobi|SGS|...>                       solver implementation.
  --iterations <integer>                          number of iterations
  --rro <double>                                  residual reduction order
  --policy <qthread|mpi|mpi3>                     dtkDistributed policy
  --np <int>                                      number of processes
  --hosts <hostname>                              hosts (multiple hosts can be specified)
  -h, --help                                      Displays this help.
  -v, --version                                   Displays version information.
  --settings <filename>                           settings file
  --verbose                                       verbose plugin initialization
  --nw, --no-window                               non GUI application (no window)
  --loglevel <trace|debug|info|warn|error|fatal>  log level used by dtkLog
  --logfile <filename | console>                  log file used by dtkLog;'
            }
        }

    Slide {
        title: "Jacobi générique vs Hypre"
        fontFamily: 'Courier New'
        content: [
        "matrice 13k x 13k, nnz: 365k,  jacobi: 1512 iter.",
        "cluster nef, nœuds Xeon 20 cœurs, infiniband 40G",
        "openmpi-1.8.5.rc1",
        " jacobi sequentiel:   5.3  sec",
        " jacobi   20 procs:   1.1  sec",
        " jacobi 2x20 procs:  13.4  sec",
        " jacobi 10x4 procs:   7.3  sec",
        " hypre     1  proc:   0.7  sec",
        " hypre   4x4 procs:   0.14 sec",
        ]
    }
    Slide {
        title: "solveur Jacobi, résultats préliminaires"
        fontFamily: 'Courier New'
        content: [
        "matrice  2M x 2M, nnz: 138M",
        "jacobi: 100 iterations",
        "cluster nef, nœuds Xeon 20 cœurs, infiniband 40G",
        "mvapich 2.1",
        " jacobi   1   proc: 188 sec",
        " jacobi  20  procs:  30 sec",
        " jacobi 4x20 procs: 101 sec",
        ]
    }

    Slide {
        title: "plugin MPI3: Retour d\'expérience"
        textFormat: Text.RichText
        content: [
        "optimisations en mémoire partagés",
        " <code> MPI_Win_allocate_shared</code>",
        " <code>MPI_Comm_split_type</code> avec MPI_COMM_TYPE_SHARED",
        "communications RMA (One Sided) with Passive target",
        "implémentations MPI3 encore peu matures: ",
        " bugs remontés à openmpi, mvapich (corrigés)",
        " mais: <i>An important part of MPI-3 deals with improved semantics and features for MPI RMA to address some of these criticisms and make MPI RMA a portable runtime system that can provide high-performance and feature-rich one-sided communication support to applications.</i> Jeff Squyres"

        ]
    }
    Slide {
        title: "Perspectives"
        textFormat: Text.RichText
        content: [
        "ADT SIMON (Jérémie Labroquère et Tristan Cabel)",
        " intégration de dtkSparseMatrix et dtkSparseSolver dans numWindSimulator (presque fait)",
        " dtkMesh basé sur dtkDistributedGraphTopology",
        " refonte de numWindSimulator basé sur dtkMesh distribué",
        " plugins MaPHyS",
        "optimisations ",
        "intégration dans le composer des structures distribuées de haut niveau",
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
