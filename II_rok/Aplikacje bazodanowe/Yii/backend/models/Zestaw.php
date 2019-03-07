<?php

namespace backend\models;

use Yii;

/**
 * This is the model class for table "zestaw".
 *
 * @property integer $id
 * @property integer $konto_id
 * @property integer $jezyk1_id
 * @property integer $jezyk2_id
 * @property integer $podkategoria_id
 * @property string $nazwa
 * @property string $zestaw
 * @property integer $ilosc_slowek
 * @property string $data_dodania
 * @property string $data_edycji
 *
 * @property Wynik[] $wyniks
 * @property Jezyk $jezyk1
 * @property Jezyk $jezyk2
 * @property Konto $konto
 * @property Podkategoria $podkategoria
 */
class Zestaw extends \yii\db\ActiveRecord
{
    /**
     * @inheritdoc
     */
    public static function tableName()
    {
        return 'zestaw';
    }

    /**
     * @inheritdoc
     */
    public function rules()
    {
        return [
            [['konto_id', 'jezyk1_id', 'jezyk2_id', 'podkategoria_id', 'nazwa', 'zestaw', 'ilosc_slowek', 'data_dodania'], 'required'],
            [['konto_id', 'jezyk1_id', 'jezyk2_id', 'podkategoria_id', 'ilosc_slowek'], 'integer'],
            [['zestaw'], 'string'],
            [['data_dodania', 'data_edycji'], 'safe'],
            [['nazwa'], 'string', 'max' => 200],
            [['jezyk1_id'], 'exist', 'skipOnError' => true, 'targetClass' => Jezyk::className(), 'targetAttribute' => ['jezyk1_id' => 'id']],
            [['jezyk2_id'], 'exist', 'skipOnError' => true, 'targetClass' => Jezyk::className(), 'targetAttribute' => ['jezyk2_id' => 'id']],
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
            'id' => 'ID',
            'konto_id' => 'Konto ID',
            'jezyk1_id' => 'Jezyk1 ID',
            'jezyk2_id' => 'Jezyk2 ID',
            'podkategoria_id' => 'Podkategoria ID',
            'nazwa' => 'Nazwa',
            'zestaw' => 'Zestaw',
            'ilosc_slowek' => 'Ilosc Slowek',
            'data_dodania' => 'Data Dodania',
            'data_edycji' => 'Data Edycji',
        ];
    }

    /**
     * @return \yii\db\ActiveQuery
     */
    public function getWyniks()
    {
        return $this->hasMany(Wynik::className(), ['zestaw_id' => 'id']);
    }

    /**
     * @return \yii\db\ActiveQuery
     */
    public function getJezyk1()
    {
        return $this->hasOne(Jezyk::className(), ['id' => 'jezyk1_id']);
    }

    /**
     * @return \yii\db\ActiveQuery
     */
    public function getJezyk2()
    {
        return $this->hasOne(Jezyk::className(), ['id' => 'jezyk2_id']);
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
