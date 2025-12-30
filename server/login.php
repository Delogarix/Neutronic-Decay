<?php
session_start();
$title = "Connexion";
?>

<!DOCTYPE html>
<html lang="fr">

    <?php require_once(__DIR__ . "/structure/head.php"); ?>

    <body class="bg-secondary">

        <?php require_once(__DIR__ . "/structure/header.php"); ?>
        <main>
            <div class="container">
                <br>
                <form class="container" action="index.php" method="post">
                    <input type="text" name="username">
                    <label>Username</label> <br>
                    <input type="password" name="password">
                    <label>Password</label> <br>
                    <button action="submit">Submit</button>
                </form>
                <br>
                <br>
                <p>Si vous n'avez pas de compte vous pouvez en crée un ici</p>
                <br>
                <form class="container" action="inscription.php" method="post">
                    <input type="text" name="new_username">
                    <label>Pseudo</label> <br>
                    <button action="submit">Inscription</button>
                </form>
            </div>
        </main>
        <?php require_once(__DIR__ . "/structure/footer.php"); ?>
    </body>
</html>