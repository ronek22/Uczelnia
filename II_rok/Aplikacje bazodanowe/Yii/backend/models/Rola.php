<?php

namespace backend\models;

use Yii;

/**
 * This is the model class for table "rola".
 *
 * @property integer $id
 * @property string $nazwa
 * @property string $opis
 *
 * @property Konto[] $kontos
 */
class Rola extends \yii\db\ActiveRecord
{
    /**
     * @inheritdoc
     */
    public static function tableName()
    {
        return 'rola';
    }

    /**
     * @inheritdoc
     */
    public function rules()
    {
        return [
            [['nazwa', 'opis'], 'required'],
            [['nazwa'], 'string', 'max' => 50],
            [['opis'], 'string', 'max' => 300],
        ];
    }

    /**
     * @inheritdoc
     */
    public function attributeLabels()
    {
        return [
            'id' => 'ID',
            'nazwa' => 'Nazwa',
            'opis' => 'Opis',
        ];
    }

    /**
     * @return \yii\db\ActiveQuery
     */
    public function getKontos()
    {
        return $this->hasMany(Konto::className(), ['rola_id' => 'id']);
    }
}
