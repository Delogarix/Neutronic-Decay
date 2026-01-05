<?php
session_start();
$title = "Connexion";
?>

<!DOCTYPE html>
<html lang="fr">

    <?php require_once(__DIR__ . "/structure/head.php"); ?>

    <body class="color-main">

        <?php require_once(__DIR__ . "/structure/header.php"); ?>
        <main>
            <div class="container flex p-2 bg-secondary rounded">
                <div class="container"><h3 class="text-center">Se connecter</h3></div>
                <form class="container form" action="index.php" method="post">
                    <label class="form-label">Nom d'utilisateur</label>
                    <input class="form-control-sm" type="text" name="username"> <br>
                    <label class="form-label">Mot de passe</label>
                    <input class="form-control-sm" type="password" name="password"> <br>
                    <button class="btn btn-outline-primary text-light" action="submit">Connexion</button>
                </form> <br>

                <div class="container"><h3 class="text-center">Crée un compte</h3></div>
                <form class="container" action="inscription.php" method="post">
                    <label class="form-label">Nouveau nom d'utilisateur</label>
                    <input class="form-control-sm" type="text" name="new_username"> <span> en minuscule </span> <br>
                    <button class="btn btn-outline-primary text-light" action="submit">Inscription</button>
                </form>
            </div>
        </main>
        <?php require_once(__DIR__ . "/structure/footer.php"); ?>
    </body>
</html>