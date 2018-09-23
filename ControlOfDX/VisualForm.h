#pragma once

#include "ControlOfDX.h"
#include "VisualRenderEventArgs.h"
#include "Resource\VisualResources.h"

namespace ControlOfDX
{
    using namespace System;
    using namespace System::Windows::Forms;;
    using namespace System::ComponentModel;

    /// <summary>DirectX�ŕ`����s���E�B���h�E�B</summary>
    public ref class VisualForm
        : System::Windows::Forms::Form
    {
    public:
        /// <summary>�`�揈���C�x���g�f���Q�[�g�B</summary>
        /// <param name="sender">�C�x���g���s���B</param>
        /// <param name="e">�C�x���g�I�u�W�F�N�g�B</param>
        delegate void VisualRenderEventHandler(Object ^ sender, VisualRenderEventArgs ^ e);

        /// <summary>���\�[�X�̏��������s���B</summary>
        [Category("DirectX")]
        [Description("���\�[�X�̏��������s��")]
        event EventHandler ^ InitializeResource;

        /// <summary>�`����s���B</summary>
        [Category("DirectX")]
        [Description("�`����s��")]
        event VisualRenderEventHandler ^ Rendering;

#pragma region "properties"
    public:
        /// <summary>���\�[�X���擾����B</summary>
        property VisualResources ^ Resources {
            VisualResources ^ get() { return this->resources; }
        }

#pragma endregion

#pragma region "fields"
    private:
        // �t�@�N�g��
        ID2D1Factory * factory;

        // DirectWrite�t�@�N�g��
        IDWriteFactory * writeFactory;

        // ���\�[�X���X�g
        VisualResources ^ resources;

        // �����_�[�^�[�Q�b�g
        ID2D1HwndRenderTarget * renderTarget;

#pragma endregion

#pragma region "constructor/destructor"
    public:
        /// <summary>�R���X�g���N�^�B</summary>
        VisualForm();

        /// <summary>�f�X�g���N�^�B</summary>
        virtual ~VisualForm();

        /// <summary>�t�@�C�i���C�U�B</summary>
        !VisualForm();

#pragma endregion

#pragma region "methods"
    private:
        /// <summary>���\�[�X�̉�����s���B</summary>
        void ReleaseResources();

        //---------------------------------------------------------------------
        // �C�x���g����
        //---------------------------------------------------------------------
    protected:
        /// <summary>�E�B���h�E�v���V�[�W���B</summary>
        /// <param name="m">���b�Z�[�W�\���́B</param>
        virtual void WndProc(System::Windows::Forms::Message% m) override;

        /// <summary>�w�i�`��C�x���g�B</summary>
        /// <param name="e">�C�x���g�I�u�W�F�N�g�B</param>
        void OnPaintBackground(PaintEventArgs ^ e) override;

        /// <summary>���\�[�X���������s���B</summary>
        /// <param name="e">�C�x���g�I�u�W�F�N�g�B</param>
        virtual void OnInitializeResource(EventArgs ^ e);

        /// <summary>�`�揈�����s���B</summary>
        /// <param name="e">�C�x���g�I�u�W�F�N�g�B</param>
        virtual void OnRendering(VisualRenderEventArgs ^ e);

        //---------------------------------------------------------------------
        // �`�揈��
        //---------------------------------------------------------------------
    private:
        /// <summary>�`����s���B</summary>
        /// <param name="hWnd">�E�B���h�E�n���h���B</param>
        void RenderControl(HWND hWnd);

        /// <summary>�f�o�C�X�ˑ����\�[�X���쐬����B</summary>
        /// <return>���s���ʁB</return>
        HRESULT CreateDeviceResources();

        /// <summary>�f�o�C�X���X�g�����A���\�[�X��������B</summary>
        void DiscardDeviceResources();

#pragma endregion
    };
}
