#pragma once

#include "ControlOfDX.h"

namespace ControlOfDX
{
    using namespace System;
    using namespace System::Collections::Generic;
    using namespace System::Windows::Forms;

    /// <summary>Direct描画ファクトリ。</summary>
    ref class SingletonFactory
    {
#pragma region "feilds"
    private:
        // Direct2Dファクトリ
        static ID2D1Factory * d2factory = NULL;

        // DirectWriteファクトリ
        static IDWriteFactory * writeFactory = NULL;

        // 登録済み使用者リスト
        static Dictionary<Control^, Control^>^ registed = gcnew Dictionary<Control^, Control^>();

#pragma endregion

#pragma region "methods"
    public:
        /// <summary>描画ファクトリの使用者登録を行う。</summary>
        /// <param name="control">使用者コントロール。</param>
        static void Regist(Control ^ control, ID2D1Factory ** d2factory, IDWriteFactory ** writeFactory)
        {
            if (!registed->ContainsKey(control)) {
                HRESULT hr;
                ID2D1Factory * d2fac;
                IDWriteFactory * writeFac;

                // Direct2Dファクトリを作成
                if (SingletonFactory::d2factory == NULL) {
                    hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &d2fac);
                    if (SUCCEEDED(hr)) {
                        SingletonFactory::d2factory = d2fac;
                    }
                    else {
                        throw gcnew InitializeException("Direct2Dファクトリの生成に失敗しました");
                    }
                }
                (*d2factory) = SingletonFactory::d2factory;

                // DirectWriteファクトリを作成
                if (SingletonFactory::writeFactory == NULL) {
                    hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), (IUnknown**)&writeFac);
                    if (SUCCEEDED(hr)) {
                        SingletonFactory::writeFactory = writeFac;
                    }
                    else {
                        throw gcnew InitializeException("DirectWriteファクトリの生成に失敗しました");
                    }
                    (*writeFactory) = SingletonFactory::writeFactory;
                }

                // 使用者登録
                registed->Add(control, control);
            }
        }

        /// <summary>描画ファクトリの使用者解除を行う。</summary>
        /// <param name="control">使用者コントロール。</param>
        static void Unregist(Control ^ control)
        {
            if (registed->ContainsKey(control)) {
                // 使用者登録を解除
                registed->Remove(control);

                // 使用者が 0になればファクトリを削除する
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
        /// <summary>Direct2Dファクトリを取得する。</summary>
        /// <return>ファクトリ。</return>
        static ID2D1Factory * GetDirect2DFactory()
        {
            return d2factory;
        }

        /// <summary>DirectWriteファクトリを取得する。</summary>
        /// <return>ファクトリ。</return>
        static IDWriteFactory * GetDirectWriteFactory()
        {
            return writeFactory;
        }

#pragma endregion
    };
}