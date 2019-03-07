<?php

namespace backend\models;

use Yii;

/**
 * This is the model class for table "jezyk".
 *
 * @property integer $id
 * @property string $nazwa
 *
 * @property Zestaw[] $zestaws
 * @property Zestaw[] $zestaws0
 */
class Jezyk extends \yii\db\ActiveRecord
{
    /**
     * @inheritdoc
     */
    public static function tableName()
    {
        return 'jezyk';
    }

    /**
     * @inheritdoc
     */
    public function rules()
    {
        return [
            [['nazwa'], 'required'],
            [['nazwa'], 'string', 'max' => 50],
        ];
    }

    /**
     * @inheritdoc
     */
    public function attributeLabels()
    {
        return [
           // 'id' => 'ID',
            'nazwa' => 'Nazwa',
        ];
    }

    /**
     * @return \yii\db\ActiveQuery
     */
    public function getZestaws()
    {
        return $this->hasMany(Zestaw::className(), ['jezyk1_id' => 'id']);
    }

    /**
     * @return \yii\db\ActiveQuery
     */
    public function getZestaws0()
    {
        return $this->hasMany(Zestaw::className(), ['jezyk2_id' => 'id']);
    }
}
