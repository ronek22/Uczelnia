<?php

use yii\helpers\Html;
use yii\widgets\ActiveForm;
use yii\helpers\ArrayHelper;
use backend\models\Rola;

/* @var $this yii\web\View */
/* @var $model backend\models\Konto */
/* @var $form yii\widgets\ActiveForm */
?>

<div class="konto-form">

    <?php $form = ActiveForm::begin(); ?>

    <?= $form->field($model, 'rola_id')->dropDownList(ArrayHelper::map(Rola::find()->asArray()->all(), 'id', 'nazwa'), ['prompt'=>'-Wybierz role-']) -> label("Rola"); ?>


    <?= $form->field($model, 'imie')->textInput(['maxlength' => true]) ?>

    <?= $form->field($model, 'nazwisko')->textInput(['maxlength' => true]) ?>

    <?= $form->field($model, 'email')->textInput(['maxlength' => true]) ?>


    <?= $form->field($model, 'status')->dropDownList([10  => 'Aktywny', 0 => 'Nieaktywny'], ['prompt'=>'-Wybierz status-']) -> label("Status"); ?>

    <div class="form-group">
        <?= Html::submitButton($model->isNewRecord ? 'Create' : 'Zmień', ['class' => $model->isNewRecord ? 'btn btn-success' : 'btn btn-primary']) ?>
    </div>

    <?php ActiveForm::end(); ?>

</div>
