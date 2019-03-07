<?php

use yii\helpers\Html;
use yii\widgets\DetailView;

/* @var $this yii\web\View */
/* @var $model backend\models\Wynik */

$this->title = $model->konto->username.' | '.$model->zestaw->nazwa;
$this->params['breadcrumbs'][] = ['label' => 'Wynik', 'url' => ['index']];
$this->params['breadcrumbs'][] = $this->title;
?>
<div class="wynik-view">

    <h1><?= Html::encode($this->title) ?></h1>

    <p>
        <?= Html::a('Zmień', ['update', 'id' => $model->id], ['class' => 'btn btn-primary']) ?>
        <?= Html::a('Usuń', ['delete', 'id' => $model->id], [
            'class' => 'btn btn-danger',
            'data' => [
                'confirm' => 'Napewno chcesz usunąć ten wynik?',
                'method' => 'post',
            ],
        ]) ?>
    </p>

    <?= DetailView::widget([
        'model' => $model,
        'attributes' => [
            //'id',
            'konto.username:text:Użytkownik',
            'zestaw.nazwa:text:Zestaw',
            'data_wyniku',
            'wynik',
        ],
    ]) ?>

</div>
