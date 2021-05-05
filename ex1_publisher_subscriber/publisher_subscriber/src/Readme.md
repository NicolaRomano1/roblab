# ESERCIZIO PUBLISHER E RECEIVER

L'esercizio chiedeva di implementare un canale di comunicazione tramite publisher e subscriber per la comunicazione delle posizioni di 6 giunti

## Messaggio utilizzato

il messaggio utilizzato per la comunicazione è JointTrajectory (<http://docs.ros.org/en/melodic/api/trajectory_msgs/html/msg/JointTrajectory.html>), sono stati utilizzati i campi joint_names per nominare i giunti e il campo positions del campo JointTrajectoryPoint (<http://docs.ros.org/en/melodic/api/trajectory_msgs/html/msg/JointTrajectoryPoint.html>)

## Publisher

Il publisher crea il messaggio nominando i giunti e assegnando valori randomici alle posizioni, pubblica poi il messaggio sul canale joints_chatter. Il messaggio inviato viene stampato anche sul terminale.

## Subscriber

Il subscriber riceve il messaggio dal canale joints_chatter. Il messaggio ricevuto viene stampato anche sul terminale.
