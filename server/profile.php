<?php
session_start();
$title="Profile";
include_once(__DIR__ . "/structure/script_data.php");


if (isset($_SESSION['logged']) && $_SESSION['logged']) {

    try {

        $db_server = new PDO(
            'mysql:host=localhost;dbname=gamedb;charset=utf8',
            'root',
            $db_passwd
        );  

        $player = $_SESSION['username'];

        $dbAllScores = 'SELECT temps FROM `SCORE` WHERE username_score = :player ORDER BY id DESC';
        $dbBestScore = 'SELECT temps as best FROM `SCORE` WHERE username_score = :player ORDER BY temps DESC LIMIT 1';
        $dbTotalGames = 'SELECT count(username_score) as games FROM `SCORE` WHERE username_score = :player';
        $dbTotalTime = 'SELECT sum(temps) as total FROM `SCORE` WHERE username_score = :player';

        $db_data = $db_server->prepare($dbAllScores);
        $db_data->execute(["player" => $player]);
        $allScores= $db_data->fetchAll();      // AllScores

        $db_data = $db_server->prepare($dbBestScore);
        $db_data->execute(["player" => $player]);
        $bestScore = $db_data->fetchAll();      // BestScore

        $db_data = $db_server->prepare($dbTotalGames);
        $db_data->execute(["player" => $player]);
        $totalGames = $db_data->fetchAll();     // TotalGames

        $db_data = $db_server->prepare($dbTotalTime);
        $db_data->execute(["player" => $player]);
        $totalTime = $db_data->fetchAll();      // TotalTime
    }

    catch (Exception $e) {
        //die('Erreur : ' . $e->getMessage());
        echo "Impossible de se connecter à la base de donnée : " . $e->getMessage(); 
    }
}

?>

<!DOCTYPE html>
<html lang="fr">

    <?php include_once(__DIR__ . "/structure/head.php"); ?>

    <body class="color-main">
        <?php include_once(__DIR__ . "/structure/header.php"); ?>

        <main class="container">

            <?php if(isset($totalGames[0]["games"]) && $totalGames[0]["games"] > 0): ?>
                
                <div class="container flex justify-content-center row">
                    <div class="col text-center bg-secondary rounded m-3">
                        <p class="gold-1">Meilleur temps</p>
                        <?php     if($bestScore[0]["best"] > $timeToFinish):?> <p class="iridium-star fw-medium">
                        <?php elseif($bestScore[0]["best"] > $timePurple): ?>  <p class="grade-purple fw-medium">
                        <?php elseif($bestScore[0]["best"] > $timePink): ?>    <p class="grade-pink   fw-strong">
                        <?php else: ?>                                   <p class="grade-silver fw-medium">
                        <?php endif ?>
                        <?= floor($bestScore[0]["best"] * 10000) / 10000 ?></p>
                    </div>
                    <div class="col text-center bg-secondary rounded m-3">
                        <p class="gold-1">Nombres de parties</p>
                        <p class="gold-2"><?= $totalGames[0]["games"] ?></p>
                    </div>
                    <div class="col text-center bg-secondary rounded m-3">
                        <p class="gold-1">Temps total</p>
                        <p class="gold-2"><?= floor($totalTime[0]["total"] * 10000) / 10000 ?></p>
                    </div>
                </div> <br>
                <div class="container p-1 rounded bg-secondary m-auto text-center">
                    <?php foreach($allScores as $score): ?>
                        <?php     if($score['temps'] > $timeToFinish):?> <p class="iridium-star fw-medium">
                        <?php elseif($score['temps'] > $timePurple): ?>  <p class="grade-purple fw-medium">
                        <?php elseif($score['temps'] > $timePink): ?>    <p class="grade-pink   fw-strong">
                        <?php else: ?>                                   <p class="grade-silver fw-medium">
                        <?php endif ?>
                        <?= floor($score['temps'] * 10000) / 10000 ?></p>
                    <?php endforeach ?>
                </div>

            <?php else: ?>
                <div class="container bg-secondary text-center rounded m-3">
                    <p class="p-2 text-light fs-5">Vous n'avez pas encore fait de partie</p>
                </div>
            <?php endif ?>

        </main>

        <?php include_once(__DIR__ . "/structure/footer.php"); ?>
    </body>
</html>