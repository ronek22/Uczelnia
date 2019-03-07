<?php
/**
 * Created by PhpStorm.
 * User: kubar
 * Date: 12.05.2017
 * Time: 13:28
 */

/* @var $this yii\web\View */
use yii\helpers\Html;

function printZestaw() {

    $num=$_GET['numer'];
    $rows = (new \yii\db\Query())
        ->select(['zestaw'])
        ->from('zestaw')
        ->where(['id' => $num])
        ->one();

    $words = explode(PHP_EOL, $rows['zestaw']);
    $words = array_map('trim', $words);

    echo '<table class="table table-striped">';
    echo '<thead><tr><th>#</th><th>Angielski</th><th>Polski</th></tr></thead>';
    echo '<tbody>';
    $i=1;
    foreach ($words as $key => $value) {
        $explode = explode(';', $value);
        if (count($explode) == 2) {
            echo '<tr><th scope="row">' . $i . '</th>';
            echo '<td>' . $explode[0] . '</td><td>' . $explode[1] . '</td></tr>';
            $i++;
        }
    }

    echo '</tbody></table>';
}

?>

<style>

    @import url('https://fonts.googleapis.com/css?family=Lato');
    @font-face {
        font-family: 'Roboto';
        font-style: normal;
        font-weight: 400;
        src: local('Roboto Regular'),
        local('Roboto-Regular'),
        url(http://themes.googleusercontent.com/static/fonts/roboto/v11/2UX7WLTfW3W8TclTUvlFyQ.woff)
        format('woff');
    }
    @font-face {
        font-family: 'Roboto';
        font-style: normal;
        font-weight: 700;
        src: local('Roboto Bold'),
        local('Roboto-Bold'),
        url(http://themes.googleusercontent.com/static/fonts/roboto/v11/d-6IYplOFocCacKzxwXSOD8E0i7KZn-EPnyo3HZu7kw.woff)
        format('woff');
    }
    @font-face {
        font-family: 'Roboto';
        font-style: italic;
        font-weight: 400;
        src: local('Roboto Italic'),
        local('Roboto-Italic'),
        url(http://themes.googleusercontent.com/static/fonts/roboto/v11/1pO9eUAp8pSF8VnRTP3xnvesZW2xOQ-xsNqO47m55DA.woff)
        format('woff');
    }


    .navbar-inverse{
        background-color: #1B1E2D;
    }

    h1 {
        font-family: 'Lato';
        font-size: 24px;
        font-style: normal;
        font-variant: normal;
        font-weight: bold;
        line-height: 66px;
    }
    h3 {
        font-family: 'Lato';
        font-size: 18px;
        font-style: normal;
        font-variant: normal;
        font-weight: 700;
        line-height: 15.4px;
    }

    body {
        font-family: 'Roboto', sans-serif;
        font-size: 13px;
        background-image: url("https://lh3.googleusercontent.com/P5RTRML8ND4rIrQzvQlYj49NyPh4YXE3GNndqp0DkKyKHoCyRTkwFhqlzkXCaIYSQHhUPRIRFRPD1BA=w1366-h588");
        background-repeat:repeat;
    }

    hr {

        border: 0;
        height: 0;
        border-top: 1px solid rgba(0, 0, 0, 0.1);
        border-bottom: 1px solid rgba(255, 255, 255, 0.3);

    }


    *:focus {
        outline: 0;
    }

</style>


<div class="site-index">

    <div class="body-content">
        <div class="container">

            <div class="row">
                <h1>Zestaw</h1>

                <?php

                    printZestaw();

                ?>

            </div>

            <hr>

            <div class="row">
                <div class="col-md-6">
                    <h3>Angielsko - Polski</h3>
                    <div class="col-md-6">

                    <details>
                        <summary>Tryb Nauki</summary>
                        <?php
                        $num=$_GET['numer'];
                        echo '<p>';
                        echo HTML::a('Alg.I Jedna próba', '?r=site%2Flearn&type=1&set='.$num.'&alg=1&step=0&xd=0');
                        echo '</p>';
                        echo '<hr>';

                        echo '<p>';
                        echo HTML::a('Alg.II Wiele prób', '?r=site%2Flearn&type=1&set='.$num.'&alg=2&step=0&xd=0');
                        echo '</p>';
                        echo '<hr>';
                        ?>
                    </details>
                    </div>
                    <div class="col-md-6">
                    <details>
                        <summary>Tryb Sprawdzania wiedzy</summary>
                        <?php
                        $num=$_GET['numer'];
                        echo '<p>';
                        echo HTML::a('Alg.I Jedna próba', '?r=site%2Ftest&type=1&set='.$num.'&alg=1&step=0&xd=0');
                        echo '</p>';
                        echo '<hr>';

                        echo '<p>';
                        echo HTML::a('Alg.II Wiele prób', '?r=site%2Ftest&type=1&set='.$num.'&alg=2&step=0&xd=0');
                        echo '</p>';
                        echo '<hr>';
                        ?>
                    </details>
                    </div>
                </div>
                <div class="col-md-6">
                    <h3>Polsko - Angielski</h3>

                    <div class="col-md-6">

                        <details>
                            <summary>Tryb Nauki</summary>
                            <?php
                            $num=$_GET['numer'];
                            echo '<p>';
                            echo HTML::a('Alg.I Jedna próba', '?r=site%2Flearn&type=2&set='.$num.'&alg=1&step=0&xd=0');
                            echo '</p>';
                            echo '<hr>';

                            echo '<p>';
                            echo HTML::a('Alg.II Wiele prób', '?r=site%2Flearn&type=2&set='.$num.'&alg=2&step=0&xd=0');
                            echo '</p>';
                            echo '<hr>';
                            ?>
                        </details>
                    </div>
                    <div class="col-md-6">
                        <details>
                            <summary>Tryb Sprawdzania wiedzy</summary>
                            <?php
                            $num=$_GET['numer'];
                            echo '<p>';
                            echo HTML::a('Alg.I Jedna próba', '?r=site%2Ftest&type=2&set='.$num.'&alg=1&step=0&xd=0');
                            echo '</p>';
                            echo '<hr>';

                            echo '<p>';
                            echo HTML::a('Alg.II Wiele prób', '?r=site%2Ftest&type=2&set='.$num.'&alg=2&step=0&xd=0');
                            echo '</p>';
                            echo '<hr>';
                            ?>
                        </details>
                    </div>
                </div>
            </div>


        </div>

    </div>
</div>
