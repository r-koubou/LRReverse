/* =========================================================================

    LRReverse.cpp

   -------------------------------------------------------------------------

   [History]
   Ver 1.00:   2015/09/18 1:12:58 R-Koubou
               1st Edition.

               Powered by http://vstcpp.wpblog.jp/

   ======================================================================== */


#include "audioeffectx.h"

#define PRESET_NUM    0 //プリセットプログラムの数
#define PARAMETER_NUM 0 //パラメータの数

#define INPUT_NUM   2 //入力数。モノラル入力=1、ステレオ入力=2
#define OUTPUT_NUM  2 //出力数。モノラル出力=1、ステレオ出力=2

#define UNIQUE_ID  'LRRV'

class LRReverse : public AudioEffectX
{
public:
    LRReverse( audioMasterCallback audioMaster );

    // 音声信号を処理するメンバー関数
    virtual void processReplacing( float** inputs, float** outputs, VstInt32 sampleFrames );
};

// ============================================================================================
// このVSTのを生成するための関数
// ============================================================================================
AudioEffect* createEffectInstance( audioMasterCallback audioMaster )
{
    //newでこのVSTを生成したポインタを返す
    return new LRReverse( audioMaster );
}

// ============================================================================================
// コンストラクタ(VSTの初期化)
// ============================================================================================
LRReverse::LRReverse( audioMasterCallback audioMaster )
    : AudioEffectX( audioMaster, PRESET_NUM, PARAMETER_NUM )
{
    //VSTの初期化を行う。

    //以下の関数を呼び出して入力数、出力数等の情報を設定する。
    //必ず呼び出さなければならない。
    setNumInputs( INPUT_NUM );    //入力数の設定
    setNumOutputs( OUTPUT_NUM );  //出力数の設定
    setUniqueID( UNIQUE_ID );     //ユニークIDの設定

    //このVSTがSynthかどうかのフラグを設定。Synthの場合…true、Effectorの場合…false
    isSynth( false );

    //このVSTが音声処理可能かどうかのフラグを設定。音声処理を行わないVSTはないので必ずこの関数を呼び出す。
    canProcessReplacing();

    //上記の関数を呼び出した後に初期化を行う

}

// ============================================================================================
// 音声信号を処理するメンバー関数
// ============================================================================================
void LRReverse::processReplacing( float** inputs, float** outputs, VstInt32 sampleFrames )
{
    int L = 0;
    int R = 1;

    for( int i = 0; i < sampleFrames; i++ )
    {
        // L<->R
        float left  = inputs[ L ][ i ];
        float right = inputs[ R ][ i ];
        outputs[ L ][ i ] = right;
        outputs[ R ][ i ] = left;
    }
}
