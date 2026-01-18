<?php
session_start();
include_once(__DIR__ . "/structure/script_data.php");

if (!isset($_SESSION['username']) || !$_SESSION['logged']) {
    die('Erreur : Impossible de se connecter à un compte ...');
}

try {

    $db_server = new PDO(
        'mysql:host=localhost;dbname=gamedb;charset=utf8',
        'root',
        $db_passwd
    );

    $content = trim(file_get_contents("php://input"));
    $decoded = json_decode($content, true);

    $dbQuery = 'INSERT INTO SCORE (temps, hasWin, username_score) VALUES (:temps, :htd, :user)';
    $dbInsert = $db_server->prepare($dbQuery);
    $dbInsert->execute(["temps" => strip_tags($decoded['score']), "htd" => strip_tags($decoded['htd']), "user" => strip_tags($_SESSION['username'])]);
    // hasWin now refers to 'HasTakeDamage' instead of the initial wining state. htd == FALSE means you beat the game without taking any damages

} catch (Exception $e) {
    die('Erreur : ' . $e->getMessage());
}
header('Content-Type: application/json; charset=utf-8');
echo json_encode($decoded);
?>