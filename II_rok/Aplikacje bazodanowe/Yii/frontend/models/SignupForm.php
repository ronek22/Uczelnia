<?php
namespace frontend\models;

use yii\base\Model;
use common\models\User;

/**
 * Signup form
 */
class SignupForm extends Model
{
    public $imie;
    public $nazwisko;
    public $username;
    public $email;
    public $password;

    public function tableName()
    {
        return 'konto';
    }

    /**
     * @inheritdoc
     */
    public function rules()
    {
        return [
            ['imie', 'trim'],
            ['imie', 'required', 'message' => "Imię nie może być puste"],
            ['imie', 'string', 'min' => 2, 'max' => 255],

            ['nazwisko', 'trim'],
            ['nazwisko', 'required','message' => "Nazwisko nie może być puste"],
            ['nazwisko', 'string', 'min' => 2, 'max' => 255],

            ['username', 'trim'],
            ['username', 'required', 'message' => "Login nie może byc pusty."],
            ['username', 'unique', 'targetClass' => '\common\models\User', 'message' => 'Ta nazwa użytkownika jest zajęta.'],
            ['username', 'string', 'min' => 2, 'max' => 255],

            ['email', 'trim'],
            ['email', 'required', 'message' => 'E-mail nie może być pusty.'],
            ['email', 'email'],
            ['email', 'string', 'max' => 255],
            ['email', 'unique', 'targetClass' => '\common\models\User', 'message' => 'Ten email jest zajety.'],

            ['password', 'required', 'message' => 'Hasło nie może pozostać bez wartości.'],
            ['password', 'string', 'min' => 6],
        ];
    }

    /**
     * Signs user up.
     *
     * @return User|null the saved model or null if saving fails
     */
    public function signup()
    {
        if (!$this->validate()) {
            return null;
        }
        
        $user = new User();
        $user->imie = $this->imie;
        $user->nazwisko = $this->nazwisko;
        $user->username = $this->username;
        $user->email = $this->email;
        $user->rola_id=4;
        $user->setPassword($this->password);
        $user->generateAuthKey();
        
        return $user->save() ? $user : null;
    }
}
