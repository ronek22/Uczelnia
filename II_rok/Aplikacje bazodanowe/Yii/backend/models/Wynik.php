<?php

namespace backend\models;

use Yii;

/**
 * This is the model class for table "wynik".
 *
 * @property integer $id
 * @property integer $konto_id
 * @property integer $zestaw_id
 * @property string $data_wyniku
 * @property integer $wynik
 *
 * @property Konto $konto
 * @property Zestaw $zestaw
 */
class Wynik extends \yii\db\ActiveRecord
{
    /**
     * @inheritdoc
     */
    public static function tableName()
    {
        return 'wynik';
    }

    /**
     * @inheritdoc
     */
    public function rules()
    {
        return [
            [['konto_id', 'zestaw_id', 'data_wyniku', 'wynik'], 'required'],
            [['konto_id', 'zestaw_id', 'wynik'], 'integer'],
            [['data_wyniku'], 'safe'],
            [['konto_id'], 'exist', 'skipOnError' => true, 'targetClass' => Konto::className(), 'targetAttribute' => ['konto_id' => 'id']],
            [['zestaw_id'], 'exist', 'skipOnError' => true, 'targetClass' => Zestaw::className(), 'targetAttribute' => ['zestaw_id' => 'id']],
        ];
    }

    /**
     * @inheritdoc
     */
    public function attributeLabels()
    {
        return [
            'id' => 'ID',
            'konto_id' => 'Konto ID',
            'zestaw_id' => 'Zestaw ID',
            'data_wyniku' => 'Data Wyniku',
            'wynik' => 'Wynik',
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
    public function getZestaw()
    {
        return $this->hasOne(Zestaw::className(), ['id' => 'zestaw_id']);
    }
}
