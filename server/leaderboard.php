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

    <body class="color-main">
        <?php require_once(__DIR__ . "/structure/header.php"); ?>

        <main class="container">
            <div class="bg-dark-subtle center rounded">
                <h1 class="text-center">Classement</h1>
            </div>
            <br>
            <div class="container">
                <table class="table table-striped table-borderless table-hover table-responsive text-center m-0 border border-black">
                    <thead class="table-dark">
                        <tr>
                            <td scope="col">Joueur</td>
                            <td scope="col">Temps</td>
                        </tr>
                    </thead>
                    <tbody > 
                        <?php if(isset($scoreboard)): ?>
                            <?php foreach($scoreboard as $score): ?>
                                <tr>
                                    <td scope="col" class="bg-secondary"><p class="fw-medium text-white"><?= $score['username_score'] ?></p></td>
                                    <td scope="col" class="iridium-star"><?= floor($score['temps'] * 10000) / 10000 ?></td>
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