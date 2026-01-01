<?php
session_start();
include_once(__DIR__ . "/structure/script_data.php");
$title = "Accueil";

if (isset ($_POST['username']) and isset($_POST['password'])) {
    if (isLoginValid($_POST['username'], $_POST['password'], $cred2)) {
        $_SESSION['username'] = strip_tags($_POST['username']);
        $_SESSION['logged'] = true;
    }
}
?>

<!DOCTYPE html>
<html lang="fr">

    <?php require_once(__DIR__ . "/structure/head.php"); ?>

    <body class="color-main">

        <?php require_once(__DIR__ . "/structure/header.php"); ?>

        <main class="container">

            <div name="erreur-login">
                <?php if (isset($_POST['username'], $_POST['password']) && !isLoginValid($_POST['username'], $_POST['password'], $cred2)): ?>
                    <h5 class="text-center bg-danger-subtle">Erreur, le mot de passe ou le nom d'utilisateur ne correspondent pas</h5>
                <?php endif ?>
            </div>

            <div class="p-4 container bg-secondary rounded">
                <div class="text-center"><h1>Neutronic-Decay</h1></div>
                <span>
                    Bienvenue sur Neutronic-Decay <br>
                    Crée un compte, jouez au jeu et atteigner le plus haut score possible dans le classement.
                </span>
                <br> <br>
                <div class="text-center"><h4>Comment jouez ?</h4></div> <br>
                <span>
                    Commencez par crée un compte <a href="login.php">ici</a>
                    puis aller sur l'onglet <strong>Jeux</strong> pour commencer la partie.
                    Sans compte vos score ne seront pas publier.
                    <br>
                    Une fois la partie lancer, survivez le plus longtemps possible en evitant les différents projectiles.
                    Chaque projectile à sa propre spécificité. Si vous perdez vous pouvez recommencer une nouvelle partie et
                    tenter de faire un meilleur score. Chaque vague de projecile surviendras toujours au même moment et du même coté
                    avec un peu d'aléatoire sur la position exacte et la direction qu'elles prennent.
                    Voyez vos meilleurs temps et celui des autres joueurs sur l'onglet <strong>Classements</strong>   
                </span>

            </div>

        </main>

        <?php require_once(__DIR__ . "/structure/footer.php"); ?>

    </body>
</html>
