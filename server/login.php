<?php
session_start();
?>

<!DOCTYPE html>
<html lang="fr">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.8/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-sRIl4kxILFvY47J16cr9ZwB07vP4J8+LH7qKQnuqkuIAvNWLzeN8tE5YBujZqJLB" crossorigin="anonymous">
        <title>ConnectionTest Login page</title>
    </head>
    <body class="bg-body-secondary">

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
    </body>
</html>