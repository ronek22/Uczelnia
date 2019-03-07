<?php
/* @var $this yii\web\View */
use yii\helpers\Html;

function ile_kat() {
    $wiersz2=(new yii\db\Query())
        ->select(['Count(*) as ile'])
        ->from('kategoria')
        ->one();

    return $wiersz2['ile'];
}

function ile_podkat($id_kat) {

    $wiersz3=(new yii\db\Query())
        ->select(['Count(*) as ile'])
        ->from('podkategoria')
        ->where(['kategoria_id' => $id_kat])
        ->one();

    return $wiersz3['ile'];
}

function ile_zestaw($id_pkat) {

    $wiersz4=(new yii\db\Query())
        ->select(['Count(*) as ile'])
        ->from('zestaw')
        ->where(['podkategoria_id' => $id_pkat])
        ->one();

    return $wiersz4['ile'];
}


$kategorie = ile_kat();
$kateg = Array();
$p=0;
$n=0;
$this->title = 'Fiszki';
?>

<style>


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
        font-weight: 500;
        line-height: 15.4px;
    }
    
    body {
        font-family: 'Roboto', sans-serif;
        font-size: 13px;
        /*margin-left:40px;*/
        /*margin-right: 40px;*/

        text-align: center;
        background-image: url("https://lh3.googleusercontent.com/P5RTRML8ND4rIrQzvQlYj49NyPh4YXE3GNndqp0DkKyKHoCyRTkwFhqlzkXCaIYSQHhUPRIRFRPD1BA=w1366-h588");
        background-repeat:repeat;
    }

    .kat {
        text-align: center !important;
    }

     .jumbotron.jumbotron-white {
         background-image: url("http://androidwallpape.rs/content/02-wallpapers/77-ghost-nebula/ghost_nebula.jpg");
         background-repeat:no-repeat;
         background-position: bottom center;
         background-size: cover;
         height: 300px;
         width:100% !important;
         border-radius: 0 !important;
     }

    .jumbotron.jumbotron-white h1  {
        color:white !important;
        padding-top: 40px !important;
    }

    .jumbotron.jumbotron-white p  {
        color:white !important;
    }




    *:focus {
        outline: 0;
    }





    /*.kat a {*/
        /*text-align: inherit !important;*/
    /*}*/

</style>

<div class="jumbotron jumbotron-white">
    <div class="container">
        <h1>Fiszki!</h1>
        <p class="lead">System nauki słówek</p>
    </div>
</div>

<div class="site-index">



    <div class="body-content">
        <div class="container">

        <div class="row">

        <?php
            $wiersz2= (new \yii\db\Query())
            ->select(['*'])
            ->from('kategoria')
            ->All();

            $i=0;
            while($i<$kategorie){
                $id = $wiersz2[$i]['id'];

                echo '<div class="col-md-4 kat"><h3>';
                echo HTML::label($wiersz2[$i]['nazwa']);
                echo '</h3>';

                $podkat=ile_podkat($id);
                $wiersz3 = (new \yii\db\Query())
                    ->select(['*'])
                    ->from('podkategoria')
                    ->All();

                $j=0;
                while($j<$podkat){
                    $id_pd = $wiersz3[$p]['id'];
                    $sumary = $wiersz3[$p]['nazwa'];
                    echo "<details><summary>$sumary</summary>";

                    $ileZestaw=ile_zestaw($id_pd);
                    $wiersz = (new \yii\db\Query())
                        ->select(['*'])
                        ->from('zestaw')
                        ->where(['podkategoria_id' => $id_pd])
                        ->All();


                    $m=0;
                    $n=0;
                    while($m<$ileZestaw){
                        $id_zes = $wiersz[$n]['id'];
                        echo '<p>';
                        echo HTML::a($wiersz[$n]['nazwa'], '?r=site%2Fzestaw&numer='.$id_zes);
                        echo '</p>';
                        echo '<hr>';
                        $n++;
                        $m++;
                    }
//                    echo HTML::a($wiersz3[$p]['nazwa'], '?r=site%2Fpodkategoria&numer='.$id);
    //                echo HTML::dropDownList($wiersz3[$i]['nazwa']);



                    echo "</details>";
                    $p++;
                    $j++;
                }

                echo '</div>';
                $i++;
            }

            ?>
        </div>
        </div>

    </div>
</div>
