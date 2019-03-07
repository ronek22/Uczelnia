<?php

use yii\helpers\Html;
use yii\widgets\ActiveForm;

/* @var $this yii\web\View */
/* @var $model backend\models\Wynik */
/* @var $form yii\widgets\ActiveForm */
?>

<div class="wynik-form">

    <?php $form = ActiveForm::begin(); ?>

    <?= $form->field($model, 'konto_id')->dropDownList($konta) ?>

    <?= $form->field($model, 'zestaw_id')->dropDownList($zestaw) ?>

    <?= $form->field($model, 'data_wyniku')->textInput() ?>

    <?= $form->field($model, 'wynik')->textInput() ?>

    <div class="form-group">
        <?= Html::submitButton($model->isNewRecord ? 'Create' : 'Update', ['class' => $model->isNewRecord ? 'btn btn-success' : 'btn btn-primary']) ?>
    </div>

    <?php ActiveForm::end(); ?>

</div>
