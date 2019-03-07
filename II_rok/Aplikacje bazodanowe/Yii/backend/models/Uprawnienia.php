<?php

namespace backend\models;

use Yii;

/**
 * This is the model class for table "uprawnienia".
 *
 * @property integer $konto_id
 * @property integer $podkategoria_id
 *
 * @property Konto $konto
 * @property Podkategoria $podkategoria
 */
class Uprawnienia extends \yii\db\ActiveRecord
{
    /**
     * @inheritdoc
     */
    public static function tableName()
    {
        return 'uprawnienia';
    }

    /**
     * @inheritdoc
     */
    public function rules()
    {
        return [
            [['konto_id', 'podkategoria_id'], 'required'],
            [['konto_id', 'podkategoria_id'], 'integer'],
            [['konto_id'], 'exist', 'skipOnError' => true, 'targetClass' => Konto::className(), 'targetAttribute' => ['konto_id' => 'id']],
            [['podkategoria_id'], 'exist', 'skipOnError' => true, 'targetClass' => Podkategoria::className(), 'targetAttribute' => ['podkategoria_id' => 'id']],
        ];
    }

    /**
     * @inheritdoc
     */
    public function attributeLabels()
    {
        return [
            'konto_id' => 'Konto ID',
            'podkategoria_id' => 'Podkategoria ID',
        ];
    }

    /**
     * @return \yii\db\ActiveQuery
     */
    public function getKonto()
    {
        return $this->hasOne(Konto::className(), ['id' => 'konto_id']);
    }

    /**
     * @return \yii\db\ActiveQuery
     */
    public function getPodkategoria()
    {
        return $this->hasOne(Podkategoria::className(), ['id' => 'podkategoria_id']);
    }
}
