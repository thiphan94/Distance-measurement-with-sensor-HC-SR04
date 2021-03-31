<?php // content="text/plain; charset=utf-8"
    require_once('jpgraph-4.3.4/src/jpgraph.php');
    require_once('jpgraph-4.3.4/src/jpgraph_line.php');
    require_once('jpgraph-4.3.4/src/jpgraph_bar.php');
    require_once ('jpgraph-4.3.4/src/jpgraph_windrose.php');
    
    $secondsWait = 1;
    header("Refresh:$secondsWait");
    
    exec('mode COM9 BAUD=9600 PARITY=N data=8 stop=1 xon=off');
    $flux =fopen("COM9", "r+");

    if (!$flux) {
    echo '<font color="red">Erreur</font>';
    }

    //Create a new SQLite3 object from a database file on the server.

    $database = new SQLite3('mysqlitedb.db');
    
    
/*    
    //----------Partie de création de table et insertion des données
    //Creer table
    $database->exec("CREATE TABLE IF NOT EXISTS US(id INTEGER NOT NULL PRIMARY KEY, resultat INTEGER)");

    echo 'Donnees:';
    sleep(1);
    
    */
    $resultat = fread($flux,10);  // lire les données

    for($i = 0; $i < 5; $i++){
    //while($resultat){
    //echo ORD($resultat);

   	 $resultat1 = ord($resultat);
   	 sleep(1);
   	 $database->exec("INSERT INTO US(resultat) VALUES('$resultat1')");  //insertion des données
    }

    //----------Partie de Graphique
    // Requête pour prendre les données
    $data1 = $database->query('SELECT * FROM US');
    $data2 = $database->query('SELECT * FROM US');
    $datay=array();
    $datax=array();
    $i = 0;
    while($row = $data1->fetchArray()){
   	 $datax[] =  $row['id'];
    
    }
    
    while($row2 = $data2->fetchArray()){
   	 $datay[] = $row2['resultat'];
    }    
    
    fclose($flux);
    $database->close();
    
    // Setup the graph
    $graph = new Graph(450,400);
    $graph->SetScale("textlin");
    
    $theme_class=new UniversalTheme;

    $graph->SetTheme($theme_class);
    $graph->img->SetAntiAliasing(false);
    $graph->title->Set('Filled Y-grid');
    $graph->SetBox(false);

    $graph->SetMargin(40,20,36,63);

    $graph->img->SetAntiAliasing();

    $graph->yaxis->HideZeroLabel();
    $graph->yaxis->HideLine(false);
    $graph->yaxis->HideTicks(false,false);

    $graph->xgrid->Show();
    $graph->xgrid->SetLineStyle("solid");
    $graph->xaxis->SetTickLabels(array());
    $graph->xgrid->SetColor('#E3E3E3');
    
    // Create the first line
    $p1 = new LinePlot($datay);
    $graph->Add($p1);
    $p1->SetColor("#6495ED");
    $p1->SetLegend('Line 1');
    
    $graph->legend->SetFrameWeight(1);

    // Output line
    $graph->Stroke();

?>



