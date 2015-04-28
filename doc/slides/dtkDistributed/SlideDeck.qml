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
            " num3sis, axel, medInria, enas, carbonQuant, pib, inalgae",
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
            "Sérialisation via le QVariant: ",
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
            title: "Messages"
            textFormat: Text.RichText
            content: [
            "échange de messages entre contrôleur, serveur et slave",
            "protocole basé sur JSON et du pseudo HTTP",
            "interface C++: <b>dtkDistributedMessage</b>",
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
            "   s\'interface avec Torque, OAR",
            "   variable d\'environnement DTK_NUM_PROCS",
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
            "déploiement de l\'application (<i>spawn</i>)",
            "exécution des taches de calcul (<i>exec</i>)"
            ]
            CodeSection {
                width: parent.width / 2.4
                anchors.right: parent.right
                text:"dtkDistributed::create(argc,argv);

QCommandLineParser *parser=app->parser();

app.initialize();

app.spawn();

app.exec(work);

app.unspawn();
"
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
  /* --nt <int>                                      number of threads (for hybrid plugins) */

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
            ,,
            "Structure de graphe simple",
            "Algorithme simple"
            ]
        }

        Slide {
            title: "Calcul de maximum sur un graphe partitionné"
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
            title: "Calcul de maximum sur un graphe partitionné"
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
            ,,,,,
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
            "Tout compte fait, on va s'en passer..."
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
            title: "dtkDistibuted Containers"
            Rectangle {
                width:  parent.width * 0.6
                height: parent.height
                anchors.centerIn: parent
                //opacity: 0.0
                color : "lightgrey"
                radius: 10
                Image {
                anchors.centerIn: parent
                width:  parent.width
                height: parent.height
                    id: dtkDistributedContainers
                    source: "images/dtkDistributed.png"
                    /* mipmap: true */
                    anchors.margins: 10
                }
            }
        }

        Slide {
            title: "dtkDistibutedArray<T>"
            Rectangle {
                width:  parent.width * 0.4
                height: parent.height
                anchors.left: parent.left
                //opacity: 0.0
                color : "lightgrey"
                radius: 10
                Image {
                width:  parent.width
                height: parent.height
                    id: dtkDistributedArrayAPI
                    source: "images/dtkDistributedArrayAPI.png"
                    /* mipmap: true */
                    anchors.margins: 10
                }
            }
            CodeSection {
                width: parent.width * 0.55
                anchors.right: parent.right
                text: "// SEQUENTIAL INITIALIZATION

qlonglong N = 16257;
dtkDistributedCommunicator *comm = 
dtkDistributed::app()->communicator();

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
comm->barrier();"
            }
        }

        Slide {
            title: "dtkDistibutedArray<T>"
            CodeSection {
                width: parent.width
                anchors.centerIn: parent.centerIn
                text: "// PARALLEL INITIALIZATION

qlonglong N = 16257;
dtkDistributedCommunicator *comm = dtkDistributed::app()->communicator();

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

comm->barrier();"
            }
        }

        Slide {
            title: "dtkDistibutedArray<T>"
            Rectangle {
                width:  parent.width * 0.45
                height: parent.height * 0.8
                anchors.left: parent.left
                //opacity: 0.0
                color : "lightgrey"
                radius: 10
                Image {
                width:  parent.width
                height: parent.height
                    id: dtkDistributedArrayAPI_global
                    source: "images/dtkDistributedArrayAPI_global.png"
                    /* mipmap: true */
                    anchors.margins: 10
                }
            }
            Rectangle {
                width:  parent.width * 0.45
                height: parent.height * 0.8
                anchors.right: parent.right
                //opacity: 0.0
                color : "lightgrey"
                radius: 10
                Image {
                width:  parent.width
                height: parent.height
                    id: dtkDistributedArrayAPI_local
                    source: "images/dtkDistributedArrayAPI_local.png"
                    /* mipmap: true */
                    anchors.margins: 10
                }
            }
            Text {
                property real fontSize: parent.height * 0.05
                property string fontFamily: parent.fontFamily;
                id : apitext
                width:  parent.width
                height: parent.height * 0.1
                text : "API globale vs API locale"
                anchors.bottom: parent.bottom
                font.family: fontFamily
                font.pixelSize: fontSize
                color: "white"
                horizontalAlignment: Text.AlignHCenter
            }
        }

        Slide {
            title: "dtkDistibutedArray<T> architecture"
            Rectangle {
                property real fontSize: parent.height * 0.05
                property string fontFamily: parent.fontFamily;
                id: array_top
                width:  parent.width * 0.8
                height: parent.height * 0.2
                anchors.top: parent.top
                anchors.horizontalCenter: parent.horizontalCenter
                color : "darkgrey"
                radius: 10
                Text {
                    id: array_top_txt0
                    width:  parent.width
                    text : "<p>dtkDistributedArray<T></p>"
                    font.bold: true
                    font.family: parent.fontFamily
                    font.pixelSize: parent.fontSize
                    color: "white"
                    horizontalAlignment: Text.AlignHCenter                    
                }
                Text {
                    id: array_top_txt1
                    anchors.top: array_top_txt0.bottom
                    width:  parent.width
                    text : "dtkDistributedMapper"
                    font.family: parent.fontFamily
                    font.pixelSize: parent.fontSize
                    color: "white"
                    horizontalAlignment: Text.AlignHCenter                    
                }
                
            }
            Rectangle {
                property real fontSize: parent.height * 0.05
                property string fontFamily: parent.fontFamily;
                id: array_left
                width:  parent.width * 0.3
                height: parent.height * 0.5
                anchors.top: array_top.bottom
                anchors.left: parent.left
                anchors.topMargin: parent.height * 0.1
                color : "darkgrey"
                radius: 10
                Text {
                    anchors.centerIn: parent
                    id: array_left_txt
                    width:  parent.width
                    text : "<p><strong>unit process #0</strong></p>
                    <p>dtkArrayData *data;</p>
                    <p>dtkDSBufferManager *bm;</p>
                    <p>dtkDSArrayCache *cache;</p>"
                    font.family: parent.fontFamily
                    font.pixelSize: parent.fontSize
                    color: "white"
                    horizontalAlignment: Text.AlignHCenter
                }
            }
            Rectangle {
                property real fontSize: parent.height * 0.05
                property string fontFamily: parent.fontFamily;
                id: array_center
                width:  parent.width * 0.3
                height: parent.height * 0.5
                anchors.top: array_top.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.topMargin: parent.height * 0.1
                color : "darkgrey"
                radius: 10
                Text {
                    anchors.centerIn: parent
                    id: array_center_txt
                    width:  parent.width
                    text : "<p><strong>unit process #1</strong></p>
                    <p>dtkArrayData *data;</p>
                    <p>dtkDSBufferManager *bm;</p>
                    <p>dtkDSArrayCache *cache;</p>"
                    font.family: parent.fontFamily
                    font.pixelSize: parent.fontSize
                    color: "white"
                    horizontalAlignment: Text.AlignHCenter
                }
            }
            Rectangle {
                property real fontSize: parent.height * 0.05
                property string fontFamily: parent.fontFamily;
                id: array_right
                width:  parent.width * 0.3
                height: parent.height * 0.5
                anchors.top: array_top.bottom
                anchors.right: parent.right
                anchors.topMargin: parent.height * 0.1
                color : "darkgrey"
                radius: 10
                Text {
                    anchors.centerIn: parent
                    id: array_right_txt
                    width:  parent.width
                    text : "<p><strong>unit process #2</strong></p>
                    <p>dtkArrayData *data;</p>
                    <p>dtkDSBufferManager *bm;</p>
                    <p>dtkDSArrayCache *cache;</p>"
                    font.family: parent.fontFamily
                    font.pixelSize: parent.fontSize
                    color: "white"
                    horizontalAlignment: Text.AlignHCenter
                }
            }
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
            ,,
            "Structure de graphe simple",
            "Algorithme simple"
            ]
        }

        Slide {
            title: "Calcul de maximum sur un graphe partitionné"
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
            title: "Calcul de maximum sur un graphe partitionné"
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
            ,,,,,
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
            "Tout compte fait, on va s'en passer..."
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
            title: "dtkDistibuted Containers"
            Rectangle {
                width:  parent.width * 0.6
                height: parent.height
                anchors.centerIn: parent
                //opacity: 0.0
                color : "lightgrey"
                radius: 10
                Image {
                anchors.centerIn: parent
                width:  parent.width
                height: parent.height
                    id: dtkDistributedContainers
                    source: "images/dtkDistributed.png"
                    /* mipmap: true */
                    anchors.margins: 10
                }
            }
        }

        Slide {
            title: "dtkDistibutedArray<T>"
            Rectangle {
                width:  parent.width * 0.4
                height: parent.height
                anchors.centerIn: parent
                //opacity: 0.0
                color : "lightgrey"
                radius: 10
                Image {
                anchors.centerIn: parent
                width:  parent.width
                height: parent.height
                    id: dtkDistributedArrayAPI
                    source: "images/dtkDistributedArrayAPI.png"
                    /* mipmap: true */
                    anchors.margins: 10
                }
            }
        }

        

        Slide {
            title: "Algèbre Linéaire Creuse"
            content: [
            "dtkDistributedSparseMatrix",
            "dtkLinearSolverSparse"
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
