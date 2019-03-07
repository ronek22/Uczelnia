<?php

use yii\helpers\Html;
use yii\widgets\ActiveForm;
use yii\helpers\ArrayHelper;
use backend\models\Konto;

/* @var $this yii\web\View */
/* @var $model backend\models\Uprawnienia */
/* @var $form yii\widgets\ActiveForm */
?>

<div class="uprawnienia-form">

    <?php $form = ActiveForm::begin(); ?>

    <?= $form->field($model, 'konto_id')->dropDownList(ArrayHelper::map(Konto::find()-> where('rola_id != 1') -> andWhere('rola_id != 4') -> asArray()->all(), 'id', 'username'), ['prompt'=>'-Wybierz użytkownika-']) -> label("Podkategoria"); ?>

    <?= $form->field($model, 'podkategoria_id')->dropDownList($podkategoria) ?>

    <div class="form-group">
        <?= Html::submitButton($model->isNewRecord ? 'Utwórz' : 'Zmień', ['class' => $model->isNewRecord ? 'btn btn-success' : 'btn btn-primary']) ?>
    </div>

    <?php ActiveForm::end(); ?>

</div>
