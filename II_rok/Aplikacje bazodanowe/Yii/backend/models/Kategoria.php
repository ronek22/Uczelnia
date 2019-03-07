<?php

namespace backend\models;

use Yii;

/**
 * This is the model class for table "kategoria".
 *
 * @property integer $id
 * @property string $nazwa
 * @property string $opis
 *
 * @property Podkategoria[] $podkategorias
 */
class Kategoria extends \yii\db\ActiveRecord
{
    /**
     * @inheritdoc
     */
    public static function tableName()
    {
        return 'kategoria';
    }

    /**
     * @inheritdoc
     */
    public function rules()
    {
        return [
            [['nazwa', 'opis'], 'required'],
            [['opis'], 'string'],
            [['nazwa'], 'string', 'max' => 50],
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
    public function getPodkategorias()
    {
        return $this->hasMany(Podkategoria::className(), ['kategoria_id' => 'id']);
    }
}
