
<?php
require_once(__DIR__ . "/structure/script_data.php");
$errorMsg = "";
$title = "Inscription";

if (isset($_POST['new_username'])) {
    $user = strip_tags($_POST['new_username']);
    if (empty($user)) {
        echo<<<END
            <p class="text-danger container">Erreur, formulaire vide</p>
END;
    }
    else {
        $newCred = ["username" => $user];
        
        if (isLoginExist($user, $cred2)) {
            $errorMsg = "Erreur, le nom d'utilisateur : " . $user . ", est déja pris";
        }
        else {
            $var1 = array_rand($pass_set, 1);
            $var2 = array_rand($pass_set, 1);
            $generatedPassword = $pass_set[$var1] . "-" . $pass_set[$var2];
            try {
                $db_server = new PDO('mysql:host=localhost;dbname=gamedb;charset=utf8','root',$db_passwd,[PDO::ATTR_ERRMODE => PDO::ERRMODE_EXCEPTION]);
                $dbQuery = 'INSERT INTO JOUEUR VALUES (:user, :passwd)';
                $dbInsert = $db_server->prepare($dbQuery);
                $dbInsert->execute(["user" => $user, "passwd" => $generatedPassword]);

            } catch (Exception $e) {
                die('Erreur : ' . $e->getMessage());
            }
            $errorMsg = "Le compte " . $user . " à bien été crée ..." . "<br>" . "Nouveau mot de passe : " . $generatedPassword . "<br>" . "Pensez à noter votre mot de passe !!!";
        }
    }
}

?>

<!DOCTYPE html>
<html lang="fr">

    <?php require_once(__DIR__ . "/structure/head.php"); ?>

    <body class="bg-body-secondary">
        <?php require_once(__DIR__ . "/structure/header.php"); ?>

        <main class="container">
            <h1>Page d'inscription</h1>
            <?= $errorMsg ?>
            <br>
        </main>

        <?php require_once(__DIR__ . "/structure/footer.php"); ?>
    </body>
</html>