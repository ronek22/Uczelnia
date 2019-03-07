<?php

use yii\helpers\Html;
use yii\widgets\ActiveForm;

/* @var $this yii\web\View */
/* @var $model backend\models\ZestawSearch */
/* @var $form yii\widgets\ActiveForm */
?>

<div class="zestaw-search">

    <?php $form = ActiveForm::begin([
        'action' => ['index'],
        'method' => 'get',
    ]); ?>

    <?= $form->field($model, 'id') ?>

    <?= $form->field($model, 'konto_id') ?>

    <?= $form->field($model, 'jezyk1_id') ?>

    <?= $form->field($model, 'jezyk2_id') ?>

    <?= $form->field($model, 'podkategoria_id') ?>

    <?php // echo $form->field($model, 'nazwa') ?>

    <?php // echo $form->field($model, 'zestaw') ?>

    <?php // echo $form->field($model, 'ilosc_slowek') ?>

    <?php // echo $form->field($model, 'data_dodania') ?>

    <?php // echo $form->field($model, 'data_edycji') ?>

    <div class="form-group">
        <?= Html::submitButton('Search', ['class' => 'btn btn-primary']) ?>
        <?= Html::resetButton('Reset', ['class' => 'btn btn-default']) ?>
    </div>

    <?php ActiveForm::end(); ?>

</div>
