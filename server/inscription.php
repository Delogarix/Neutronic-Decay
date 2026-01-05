
<?php
require_once(__DIR__ . "/structure/script_data.php");
$errorMsg = "";
$title = "Inscription";

if (isset($_POST['new_username'])) {
    $user = strip_tags($_POST['new_username']);
    $user = strtolower($user);
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
            $succes = true;
        }
    }
}

?>

<!DOCTYPE html>
<html lang="fr">

    <?php require_once(__DIR__ . "/structure/head.php"); ?>

    <body class="color-main">
        <?php require_once(__DIR__ . "/structure/header.php"); ?>

        <main class="container">
            <div class="container bg-secondary rounded">
                <div class="container">
                    <h3 class="text-center">Inscription</h3>
                    <div class="container mb-2 bg-secondary-subtle border rounded">
                        <?php if (isset($succes) && $succes === true): ?>
                            <span class="fs-4">
                                Le compte : <span class="purple-1"><?= $user ?></span>
                                 à bien été crée
                            </span> <br>
                            <span class="fs-4">
                                Mot de passe : <span class="purple-1"><?= $generatedPassword ?></span>
                            </span> <br>
                            <span class="fs-4">
                                Noté votre mot de passe, il ne sera plus accessible dès que vous aurez quitté cette page
                            </span>
                        <?php else: ?>
                            <p class="text-danger fs-4"><?= $errorMsg ?></p>
                        <?php endif ?>
                    </div>
                    <br>
                </div>
            </div>
        </main>

        <?php require_once(__DIR__ . "/structure/footer.php"); ?>
    </body>
</html>