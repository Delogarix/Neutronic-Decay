<?php
session_start();

include_once(__DIR__ . "/structure/script_data.php");

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
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.8/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-sRIl4kxILFvY47J16cr9ZwB07vP4J8+LH7qKQnuqkuIAvNWLzeN8tE5YBujZqJLB" crossorigin="anonymous">
        <title>Leaderboard</title>
    </head>
    <body class="bg-body-secondary">
        <?php require_once(__DIR__ . "/structure/header.php"); ?>

        <main class="container">
            <p>
                <?php if (isset($_SESSION['logged'])): ?>
                    <?= "Connecté en tant que : " . $_SESSION['username']; ?>
                <?php else: ?>
                    <p>Pas de session en cours</p>
                <?php endif ?>
            </p>
            <div class="bg-dark-subtle center border border-danger-subtle rounded">
                <h1 class="text-center text-danger-emphasis">LEADERBOARD</h1>
            </div>
            <br>
            <div class="container">
                <form action="leaderboard.php" method="post">
                    <label>Temps</label>
                    <input type="text" name="temps">
                    <button class="button bg-primary-subtle rounded-pill" action="submit">Envoyez</button>
                </form>
            </div>
            <br>
            <div class="container bg-secondary rounded">
                <p>zada</p>
                <table class="table table-striped table-hover">
                    <thead>
                        <tr>
                            <td>Joueur</td>
                            <td>Temps max</td>
                            <td>Niveau terminé</td>
                        </tr>
                    </thead>
                    <tbody>
                        <?php foreach($scoreboard as $score): ?>
                            <tr>
                                <td><?= $score['username_score'] ?></td>
                                <td><?= floor($score['temps'] * 10000) / 10000 ?></td>
                                <td>
                                    <?php if($score['hasWin'] == 1): ?>
                                        <?= "Oui"?>
                                    <?php endif ?>
                                </td>
                            </tr>
                        <?php endforeach ?>
                    </tbody>
                </table>
                <br>
            </div>
        </main>
        <footer class="navbar fixed-bottom">

        </footer>
    </body>
</html>