<?php

use yii\helpers\Html;

/* @var $this yii\web\View */
/* @var $model backend\models\Konto */

$this->title = 'Konto użytkownika: ' . $model->username;

$this->params['breadcrumbs'][] = ['label' => 'Konta', 'url' => ['index']];
$this->params['breadcrumbs'][] = ['label' => $model->username, 'url' => ['view', 'id' => $model->id]];
$this->params['breadcrumbs'][] = 'Formularz';
?>
<div class="konto-update">

    <h1><?= Html::encode($this->title) ?></h1>

    <?= $this->render('_form', [
        'model' => $model,
    ]) ?>

</div>
