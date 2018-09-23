#pragma once

namespace ControlOfDX
{
    using namespace System;

    /// <summary>��������O��\������B</summary>
    public ref class InitializeException
        : Exception
    {
    public:
        /// <summary>�f�t�H���g�R���X�g���N�^�B</summary>
        InitializeException()
            : Exception()
        {}

        /// <summary>�R���X�g���N�^�B</summary>
        /// <param name="message">��O���b�Z�[�W�B</param>
        InitializeException(String ^ message)
            : Exception(message)
        {}

        /// <summary>�R���X�g���N�^�B</summary>
        /// <param name="message">��O���b�Z�[�W�B</param>
        /// <param name="innerException">������O�Q�ƁB</param>
        InitializeException(String ^ message, Exception ^ innerException)
            : Exception(message, innerException)
        {}

        virtual ~InitializeException()
        {}
    };
}

