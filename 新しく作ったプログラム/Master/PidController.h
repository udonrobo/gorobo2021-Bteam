/**
 *      @file   PidController.h
 *      @brief  PIDコントローラクラス
 *      @author 谷川　豊章
 *      @date   2016/8/21
 */

#ifndef DEF_PidController_H
#define DEF_PidController_H

#include <arduino.h>

/**     PidControllerクラス
 *      PIDコントローラクラス
 */
class PidController{
protected:
    double kPro;    ///< 比例定数
    double kInt;    ///< 積分定数
    double kDif;    ///< 微分定数

    double power;       ///< 操作量
    double lastError;   ///< 過去の偏差

    double proPower;    ///< 比例量
    double intPower;    ///< 積分量
    double difPower;    ///< 微分量

    const double MAX_INT_POWER; ///< 積分量の最大値
    const double INTERVAL_S;   ///< Updateの呼び出される周期(unit:sec)
    
    PidController(const PidController&);
    PidController& operator=(const PidController&);
    
public:

    /**     コンストラクタ
     *      @param  kPro            比例係数
     *      @param  kInt            積分係数
     *      @param  kDif            微分係数
     *      @param  callInterval_us Update()の呼び出し周期
     *      @param  maxIntPower     積分量の最大値
     */
    PidController(double kPro, double kInt, double kDif, unsigned long callInterval_us, double maxIntPower = 1023.0)
        : kPro(kPro), kInt(kInt), kDif(kDif), power(0), lastError(0), proPower(0), intPower(0), difPower(0), MAX_INT_POWER(maxIntPower), INTERVAL_S( double(callInterval_us)/1000000.0 )
    { }

    /**     デストラクタ
     */
    virtual ~PidController(){}

    /**     データ更新
     *      @param  controlValue    制御量
     *      @param  targetValue     目標値
     */
    virtual void Update(double controlValue, double targetValue){
        //偏差の計算
        double error = targetValue - controlValue;  

        //比例量の計算
        proPower = kPro * error;

        //積分量の計算
        intPower += kInt * error * INTERVAL_S;
        intPower = constrain(intPower, -MAX_INT_POWER, MAX_INT_POWER);

        //微分量の計算
        difPower = kDif * (error - lastError) / INTERVAL_S;

        //操作量の計算
        power = proPower + intPower + difPower;

        //偏差の保存
        lastError = error;
    }

    /**     操作量の取得
     *      @return 操作量
     */
    double GetPower(){
        return power;
    }

    /**     操作量のクリア
     *      内部の量をすべて0にする。
     */
    virtual void ClearPower(){
        proPower = 0.0;
        intPower = 0.0;
        difPower = 0.0;
        power = 0.0;
        lastError = 0.0;
    }


    /**     比例係数の設定
     *      @param  kPro    比例係数の値
     */
    void SetParamPro(double kPro){
        this->kPro = kPro;
    }
    
    /**     積分係数の設定
     *      @param  kInt    積分係数の値
     */
    void SetParamInt(double kInt){
        this->kInt = kInt;
    }
    
    /**     微分係数の設定
     *      @param  kDif    微分係数の値
     */
    void SetParamDif(double kDif){
        this->kDif = kDif;
    }


    /**     比例量の取得
     *      @return 比例量
     */
    double GetProPower(){
        return proPower;
    }

    /**     積分量の取得
     *      @return 積分量
     */
    double GetIntPower(){
        return intPower;
    }

    /**     微分量の取得
     *      @return 微分量
     */
    double GetDifPower(){
        return difPower;
    }

};

#endif
