/* =========================================================================

    LRReverse.cpp

   -------------------------------------------------------------------------

   [History]
   Ver 1.00:   2015/09/18 1:12:58 R-Koubou
               1st Edition.

               Powered by http://vstcpp.wpblog.jp/

   ======================================================================== */


#include "audioeffectx.h"

#define PRESET_NUM    0 //�v���Z�b�g�v���O�����̐�
#define PARAMETER_NUM 0 //�p�����[�^�̐�

#define INPUT_NUM   2 //���͐��B���m��������=1�A�X�e���I����=2
#define OUTPUT_NUM  2 //�o�͐��B���m�����o��=1�A�X�e���I�o��=2

#define UNIQUE_ID  'LRRV'

class LRReverse : public AudioEffectX
{
public:
    LRReverse( audioMasterCallback audioMaster );

    // �����M�����������郁���o�[�֐�
    virtual void processReplacing( float** inputs, float** outputs, VstInt32 sampleFrames );
};

// ============================================================================================
// ����VST�̂𐶐����邽�߂̊֐�
// ============================================================================================
AudioEffect* createEffectInstance( audioMasterCallback audioMaster )
{
    //new�ł���VST�𐶐������|�C���^��Ԃ�
    return new LRReverse( audioMaster );
}

// ============================================================================================
// �R���X�g���N�^(VST�̏�����)
// ============================================================================================
LRReverse::LRReverse( audioMasterCallback audioMaster )
    : AudioEffectX( audioMaster, PRESET_NUM, PARAMETER_NUM )
{
    //VST�̏��������s���B

    //�ȉ��̊֐����Ăяo���ē��͐��A�o�͐����̏���ݒ肷��B
    //�K���Ăяo���Ȃ���΂Ȃ�Ȃ��B
    setNumInputs( INPUT_NUM );    //���͐��̐ݒ�
    setNumOutputs( OUTPUT_NUM );  //�o�͐��̐ݒ�
    setUniqueID( UNIQUE_ID );     //���j�[�NID�̐ݒ�

    //����VST��Synth���ǂ����̃t���O��ݒ�BSynth�̏ꍇ�ctrue�AEffector�̏ꍇ�cfalse
    isSynth( false );

    //����VST�����������\���ǂ����̃t���O��ݒ�B�����������s��Ȃ�VST�͂Ȃ��̂ŕK�����̊֐����Ăяo���B
    canProcessReplacing();

    //��L�̊֐����Ăяo������ɏ��������s��

}

// ============================================================================================
// �����M�����������郁���o�[�֐�
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
