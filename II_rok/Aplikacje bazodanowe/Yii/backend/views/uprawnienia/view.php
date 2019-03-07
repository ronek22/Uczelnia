<?php

use backend\models\Konto;
use yii\helpers\Html;
use yii\widgets\DetailView;

/* @var $this yii\web\View */
/* @var $model backend\models\Uprawnienia */

$this->title = $model->konto->username;
$this->params['breadcrumbs'][] = ['label' => 'Uprawnienias', 'url' => ['index']];
$this->params['breadcrumbs'][] = $this->title;
?>
<div class="uprawnienia-view">

    <h1><?= Html::encode($this->title) ?></h1>

    <p>
        <?= Html::a('Zmień', ['update', 'konto_id' => $model->konto_id, 'podkategoria_id' => $model->podkategoria_id], ['class' => 'btn btn-primary']) ?>
        <?= Html::a('Usuń', ['delete', 'konto_id' => $model->konto_id, 'podkategoria_id' => $model->podkategoria_id], [
            'class' => 'btn btn-danger',
            'data' => [
                'confirm' => 'Jesteś pewny, że chcesz usunąć te uprawnienie?',
                'method' => 'post',
            ],
        ]) ?>
    </p>

    <?= DetailView::widget([
        'model' => $model,
        'attributes' => [
            'konto.username',
            'podkategoria.nazwa',
        ],
    ]) ?>

</div>
