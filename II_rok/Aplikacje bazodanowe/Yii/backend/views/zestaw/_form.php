<?php

use yii\helpers\Html;
use yii\widgets\ActiveForm;
use backend\models\Konto;
use yii\helpers\ArrayHelper;

/* @var $this yii\web\View */
/* @var $model backend\models\Zestaw */
/* @var $form yii\widgets\ActiveForm */
?>

<div class="zestaw-form">

    <?php $form = ActiveForm::begin(); ?>

    <?php
    if($model->isNewRecord) {
        echo $form->field($model, 'konto_id')->hiddenInput(['value' => Yii::$app->user->identity->getId()])->label(false);
    }
    ?>

    <?= $form->field($model, 'jezyk1_id')->dropDownList($jezyk) ?>

    <?= $form->field($model, 'jezyk2_id')->dropDownList($jezyk) ?>

    <?php
    $role = Konto::getRole(Yii::$app -> user -> id) ->rola_id;
    if ($role == 2 || $role == 3) {
        echo $form->field($model, 'podkategoria_id')->dropDownList(ArrayHelper::map((new \yii\db\Query())->select(['p.id', 'p.nazwa'])->from('podkategoria p')->innerJoin('uprawnienia u', 'p.id = u.podkategoria_id')->where(['konto_id' => Yii::$app->user->id])->all(), 'id', 'nazwa'), ['prompt' => '-Wybierz podkategorie-'])->label("Podkategoria");
    } else {
        echo $form->field($model, 'podkategoria_id')->dropDownList(ArrayHelper::map(Podkategoria::find()->asArray()->all(), 'id', 'nazwa'), ['prompt' => '-Wybierz podkategorie-'])->label("Podkategoria");
    }
    ?>

    <?= $form->field($model, 'nazwa')->textInput(['maxlength' => true]) ?>

    <?= $form->field($model, 'zestaw')->textarea(['rows' => 6]) ?>

    <?= $form->field($model, 'ilosc_slowek')->textInput() ?>

    <?= $form->field($model, 'data_dodania')->hiddenInput(['value'=> date('Y-m-d')]) -> label(false); ?>


    <div class="form-group">
        <?= Html::submitButton($model->isNewRecord ? 'Utwórz' : 'Zmień', ['class' => $model->isNewRecord ? 'btn btn-success' : 'btn btn-primary']) ?>
    </div>

    <?php ActiveForm::end(); ?>

</div>
