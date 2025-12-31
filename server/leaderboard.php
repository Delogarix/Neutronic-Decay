<?php
session_start();
include_once(__DIR__ . "/structure/script_data.php");
$title = "Classement";

if (isset($_POST['temps'], $_SESSION['logged'])) {
    try {
        $db_server = new PDO('mysql:host=localhost;dbname=gamedb;charset=utf8','root',$db_passwd,[PDO::ATTR_ERRMODE => PDO::ERRMODE_EXCEPTION]);
        $win = 0;
        if ($_POST['temps'] >= $timeToFinish) $win = 1;
        $dbQuery = 'INSERT INTO SCORE (temps, hasWin, username_score) VALUES (:temps, :win, :user)';
        $dbInsert = $db_server->prepare($dbQuery);
        $dbInsert->execute(["temps" => $_POST['temps'], "win" => $win, "user" => $_SESSION['username']]);

    } catch (Exception $e) {
        die('Erreur : ' . $e->getMessage());
    }
}

?>

<!DOCTYPE html>
<html lang="fr">

    <?php require_once(__DIR__ . "/structure/head.php"); ?>

    <body class="bg-secondary">
        <?php require_once(__DIR__ . "/structure/header.php"); ?>

        <main class="container-fluid">
            <div class="bg-dark-subtle center border border-danger-subtle rounded">
                <h1 class="text-center text-danger-emphasis">LEADERBOARD</h1>
            </div>
            <br>
            <div class="container-fluid bg-secondary rounded">
                <table class="table table-striped table-hover">
                    <thead>
                        <tr>
                            <td>Joueur</td>
                            <td>Temps max</td>
                            <td>Niveau terminé</td>
                        </tr>
                    </thead>
                    <tbody>
                        <?php if(isset($scoreboard)): ?>
                            <?php foreach($scoreboard as $score): ?>
                                <tr>
                                    <td><?= $score['username_score'] ?></td>
                                    <td class="iridium-star"><?= floor($score['temps'] * 10000) / 10000 ?></td>
                                    <td>
                                        <?php if($score['hasWin'] == 1): ?>
                                            <?= "Oui"?>
                                        <?php endif ?>
                                    </td>
                                </tr>
                            <?php endforeach ?>
                        <?php endif ?>
                    </tbody>
                </table>
                <br>
            </div>
        </main>
        <?php require_once(__DIR__ . "/structure/footer.php"); ?>
    </body>
</html>