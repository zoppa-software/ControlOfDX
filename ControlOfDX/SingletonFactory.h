#pragma once

#include "ControlOfDX.h"

namespace ControlOfDX
{
    using namespace System;
    using namespace System::Collections::Generic;
    using namespace System::Windows::Forms;

    /// <summary>Direct�`��t�@�N�g���B</summary>
    ref class SingletonFactory
    {
#pragma region "feilds"
    private:
        // Direct2D�t�@�N�g��
        static ID2D1Factory * d2factory = NULL;

        // DirectWrite�t�@�N�g��
        static IDWriteFactory * writeFactory = NULL;

        // �o�^�ςݎg�p�҃��X�g
        static Dictionary<Control^, Control^>^ registed = gcnew Dictionary<Control^, Control^>();

#pragma endregion

#pragma region "methods"
    public:
        /// <summary>�`��t�@�N�g���̎g�p�ғo�^���s���B</summary>
        /// <param name="control">�g�p�҃R���g���[���B</param>
        static void Regist(Control ^ control, ID2D1Factory ** d2factory, IDWriteFactory ** writeFactory)
        {
            if (!registed->ContainsKey(control)) {
                HRESULT hr;
                ID2D1Factory * d2fac;
                IDWriteFactory * writeFac;

                // Direct2D�t�@�N�g�����쐬
                if (SingletonFactory::d2factory == NULL) {
                    hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &d2fac);
                    if (SUCCEEDED(hr)) {
                        SingletonFactory::d2factory = d2fac;
                    }
                    else {
                        throw gcnew InitializeException("Direct2D�t�@�N�g���̐����Ɏ��s���܂���");
                    }
                }
                (*d2factory) = SingletonFactory::d2factory;

                // DirectWrite�t�@�N�g�����쐬
                if (SingletonFactory::writeFactory == NULL) {
                    hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), (IUnknown**)&writeFac);
                    if (SUCCEEDED(hr)) {
                        SingletonFactory::writeFactory = writeFac;
                    }
                    else {
                        throw gcnew InitializeException("DirectWrite�t�@�N�g���̐����Ɏ��s���܂���");
                    }
                    (*writeFactory) = SingletonFactory::writeFactory;
                }

                // �g�p�ғo�^
                registed->Add(control, control);
            }
        }

        /// <summary>�`��t�@�N�g���̎g�p�҉������s���B</summary>
        /// <param name="control">�g�p�҃R���g���[���B</param>
        static void Unregist(Control ^ control)
        {
            if (registed->ContainsKey(control)) {
                // �g�p�ғo�^������
                registed->Remove(control);

                // �g�p�҂� 0�ɂȂ�΃t�@�N�g�����폜����
                if (registed->Count <= 0) {
                    if (SingletonFactory::d2factory != NULL) {
                        SingletonFactory::d2factory->Release();
                        SingletonFactory::d2factory = NULL;
                    }

                    if (SingletonFactory::writeFactory != NULL) {
                        SingletonFactory::writeFactory->Release();
                        SingletonFactory::writeFactory = NULL;
                    }
                }
            }
        }

    internal:
        /// <summary>Direct2D�t�@�N�g�����擾����B</summary>
        /// <return>�t�@�N�g���B</return>
        static ID2D1Factory * GetDirect2DFactory()
        {
            return d2factory;
        }

        /// <summary>DirectWrite�t�@�N�g�����擾����B</summary>
        /// <return>�t�@�N�g���B</return>
        static IDWriteFactory * GetDirectWriteFactory()
        {
            return writeFactory;
        }

#pragma endregion
    };
}