<?php

use yii\helpers\Html;


/* @var $this yii\web\View */
/* @var $model backend\models\Rola */

$this->title = 'Create Rola';
$this->params['breadcrumbs'][] = ['label' => 'Rolas', 'url' => ['index']];
$this->params['breadcrumbs'][] = $this->title;
?>
<div class="rola-create">

    <h1><?= Html::encode($this->title) ?></h1>

    <?= $this->render('_form', [
        'model' => $model,
    ]) ?>

</div>
