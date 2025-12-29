<?php
session_start();
include_once(__DIR__ . "/structure/script_data.php");

if (isset ($_POST['username']) and isset($_POST['password'])) {
    if (isLoginValid($_POST['username'], $_POST['password'], $cred2)) {
        $_SESSION['username'] = $_POST['username'];
        $_SESSION['logged'] = true;
        print_r($_SESSION);
    }
}
?>

<!DOCTYPE html>
<html lang="fr">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.8/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-sRIl4kxILFvY47J16cr9ZwB07vP4J8+LH7qKQnuqkuIAvNWLzeN8tE5YBujZqJLB" crossorigin="anonymous">
        <title>ConnectionTest</title>
    </head>
    <body class=" color-main">
        <?php require_once(__DIR__ . "/structure/header.php"); ?>

        <main class="container">
        </main>
        <footer class="navbar fixed-bottom">
        </footer>
    </body>
</html>
