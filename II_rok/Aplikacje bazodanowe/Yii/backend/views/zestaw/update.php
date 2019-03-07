<?php

use yii\helpers\Html;

/* @var $this yii\web\View */
/* @var $model backend\models\Zestaw */

$this->title = 'Modyfikuj Zestaw: ' . $model->nazwa;
$this->params['breadcrumbs'][] = ['label' => 'Zestaw', 'url' => ['index']];
$this->params['breadcrumbs'][] = ['label' => $model->nazwa, 'url' => ['view', 'id' => $model->id]];
$this->params['breadcrumbs'][] = 'Update';
?>
<div class="zestaw-update">

    <h1><?= Html::encode($this->title) ?></h1>

    <?= $this->render('_form', [
        'model' => $model,
        'podkategoria' => $podkategoria,
        'konta' => $konta,
        'jezyk' => $jezyk,
    ]) ?>

</div>
