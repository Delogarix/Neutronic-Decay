<header>
    <nav class="navbar justify-content-center">
        <ul class="list-group list-group-horizontal row">
            <li class="list-group-item col "><a class="purple-1" href="index.php">Accueil</a></li>

            <?php if (isset($_SESSION['logged']) && $_SESSION['logged']): ?>
                <li class="list-group-item col"> <a class="purple-1" href="leaderboard.php">Classement</a></li>
            <?php endif ?>

            <?php if(isset($_SESSION['logged']) && $_SESSION['logged'] ): ?>
                <li class="list-group-item col"><a class="purple-1" href="../build/game.html">Jeux</a></li>
            <?php endif ?>

            <?php if(isset($_SESSION['logged']) && $_SESSION['logged']): ?>
                <li class="list-group-item col"><a class="purple-1" href="disconnect.php">Se déconnecter</a></li>
            <?php else: ?>
                <li class="list-group-item col"><a class="purple-1" href="login.php">Connexion</a></li>
            <?php endif ?>
        </ul>
    </nav>
    <br>
    <div class="container">
        <?php if (isset($_SESSION['logged'])): ?>
            <p>Connecté en tant que : </p>
            <p class="purple-1"><?= "[" . $_SESSION['username'] . "]"?></p>
        <?php else: ?>
            <p>Pas de session en cours</p>
        <?php endif ?>
    </div>
</header>