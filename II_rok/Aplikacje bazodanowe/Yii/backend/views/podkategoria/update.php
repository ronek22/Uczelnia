<?php

use yii\helpers\Html;

/* @var $this yii\web\View */
/* @var $model backend\models\Podkategoria */

$this->title = 'Zmodyfikuj Podkategorie: ' . $model->id;
$this->params['breadcrumbs'][] = ['label' => 'Podkategoria', 'url' => ['index']];
$this->params['breadcrumbs'][] = ['label' => $model->id, 'url' => ['view', 'id' => $model->id]];
$this->params['breadcrumbs'][] = 'Zmień';
?>
<div class="podkategoria-update">

    <h1><?= Html::encode($this->title) ?></h1>

    <?= $this->render('_form', [
        'model' => $model,
        'kategorie' => $kategorie,
    ]) ?>

</div>
