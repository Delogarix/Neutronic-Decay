<?php
//<nav class="d-flex container navbar justify-content-center border-bottom">
//  <ul class="list-group list-group-horizontal row">
 ?>

<br>
<header class="container">
    <nav class="navbar navbar-expand-lg bg-nav rounded">
        <div class="container-fluid">
            <a class="nav-brand m-1" href="#">
                <img src="icons/iridium-star-icon1.png" alt="logo-nd">
            </a>
            <ul class="navbar-nav justify-content-lg-center">
                <li class="list-group-item m-3 col"><a class="purple-1 nav-link" href="index.php">Accueil</a></li>
                <li class="list-group-item m-3 col"> <a class="purple-1 nav-link" href="leaderboard.php">Classement</a></li>

                <?php if(isset($_SESSION['logged']) && $_SESSION['logged'] ): ?>
                    <li class="list-group-item m-3 col"><a class="purple-1 nav-link" href="../build/game.html">Jeux</a></li>
                <?php endif ?>

                <?php if(!isset($_SESSION['logged'])): ?>
                    <li class="list-group-item m-3 col"><a class="purple-1 nav-link" href="login.php">Connexion</a></li>
                <?php endif ?>
            </ul>
            <div>
                <?php if(isset($_SESSION['logged']) && $_SESSION['logged']): ?>
                    <li class="list-group-item m-3 col d-lg-flex  justify-content-lg-end"><a class="purple-1 nav-link" href="disconnect.php">Se déconnecter</a></li>
                <?php endif ?>
            </div>
        </div>
    </nav>
    <br>
    <div class="container mb-3">
        <?php if (isset($_SESSION['logged'])): ?>
            <span>Connecté en tant que : </span>
            <span class="purple-2"><?= "[" . $_SESSION['username'] . "]"?></span>
        <?php else: ?>
            <p>Pas de session en cours</p>
        <?php endif ?>
    </div>
</header>