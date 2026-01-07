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
                <div class="text-center mt-2">
                    <img class="pixel mb-4" src="icons/nd-main-frame.png" alt="image neutronic-decay" width="40%">
                </div>
                <span class="gold-1">
                    Bienvenue sur Neutronic-Decay <br>
                    Créez un compte, jouez au jeu et atteignez le plus haut score possible dans le classement.
                </span>
                <br> <br>
                <div class="text-center"><h4 class="gold-1">Rejoindre le classement</h4></div> <br>
                <span class="gold-1">
                    Commencez par créer un compte sur l'onglet de <strong>Connexion</strong>.
                    Puis aller sur l'onglet <strong>Jeux</strong> pour commencer la partie.
                    Sans compte vos scores ne seront pas publiés.
                    <br>
                    Une fois la partie lancée, survivez le plus longtemps possible en évitant les différents projectiles.
                    Chaque projectile a sa propre spécificité. Si vous perdez, vous pouvez recommencer une nouvelle partie et
                    tenter de faire un meilleur score.
                </span>
                <div class="text-center"><h4 class="gold-1">Controle</h4></div> <br>
                <span class="gold-1">
                    Utilisez les flèches directionnelles ou [ZQSD] pour vous déplacer, [R] pour commencer et recommencer une partie. <br>
                    Les déplacements en diagonale sont plus rapides qu'en longueur. <br>
                    Chaque vague de projectile surviendra toujours au même moment et du même côté
                    avec un peu d'aléatoire sur la position exacte et la direction qu'elles prennent. <br>
                </span>
                <span class="gold-1">
                    Il existe une fin au jeu, la verrez-vous ?
                </span>
            </div>

        </main>
        <br>
        <?php require_once(__DIR__ . "/structure/footer.php"); ?>

    </body>
</html>
