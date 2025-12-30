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

    <body class=" color-main">
        <?php require_once(__DIR__ . "/structure/header.php"); ?>

        <main class="container">
            <div class="container">
                <?php if (isset($_POST['username'], $_POST['password']) && !isLoginValid($_POST['username'], $_POST['password'], $cred2)): ?>
                    <h5 class="text-center bg-danger-subtle">Erreur, le mot de passe ou le nom d'utilisateur ne correspondent pas</h5>
                <?php endif ?>
            </div>
        </main>
        <?php require_once(__DIR__ . "/structure/footer.php"); ?>
    </body>
</html>
