
<?php
require_once(__DIR__ . "/structure/script_data.php");
$errorMsg = "";

if (isset($_POST['new_username'], $_POST['new_password'])) {
    $user = $_POST['new_username'];
    $passwd = $_POST['new_password'];
    if (empty($user) || empty($passwd)) {
        echo<<<END
            <p class="text-danger container">Erreur, formulaire vide</p>
END;
    }
    else {
        $newCred = ["username" => $user, "password" => $passwd];
        
        if (isLoginExist($user, $cred2)) {
            $errorMsg = "Erreur, le nom d'utilisateur : " . $user . ", est déja pris";
        }
        else {

            try {
                $db_server = new PDO('mysql:host=localhost;dbname=testdb;charset=utf8','root',$db_passwd,[PDO::ATTR_ERRMODE => PDO::ERRMODE_EXCEPTION]);
                $dbQuery = 'INSERT INTO JOUEUR VALUES (:user, :passwd)';
                $dbInsert = $db_server->prepare($dbQuery);
                $dbInsert->execute(["user" => $user, "passwd" => $passwd]);

            } catch (Exception $e) {
                die('Erreur : ' . $e->getMessage());
            }

            $errorMsg = "Le compte a bien été crée ...";
        }
    }
}

?>

<!DOCTYPE html>
<html lang="fr">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.8/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-sRIl4kxILFvY47J16cr9ZwB07vP4J8+LH7qKQnuqkuIAvNWLzeN8tE5YBujZqJLB" crossorigin="anonymous">
        <title>Inscription</title>
    </head>
    <body class="bg-body-secondary">
        <?php require_once(__DIR__ . "/structure/header.php"); ?>
        <main class="container">
            <h1>Page d'inscription</h1>
            <?= $errorMsg ?>
            <br>
        </main>
        <footer class="navbar fixed-bottom">
            <p>copyright C starfield - 2026</p>
        </footer>
    </body>
</html>