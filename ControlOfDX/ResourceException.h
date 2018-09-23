#pragma once

namespace ControlOfDX
{
    using namespace System;

    /// <summary>���\�[�X��O��\������B</summary>
    public ref class ResourceException
        : Exception
    {
    public:
        /// <summary>�f�t�H���g�R���X�g���N�^�B</summary>
        ResourceException()
            : Exception()
        {}

        /// <summary>�R���X�g���N�^�B</summary>
        /// <param name="message">��O���b�Z�[�W�B</param>
        ResourceException(String ^ message)
            : Exception(message)
        {}

        /// <summary>�R���X�g���N�^�B</summary>
        /// <param name="message">��O���b�Z�[�W�B</param>
        /// <param name="innerException">������O�Q�ƁB</param>
        ResourceException(String ^ message, Exception ^ innerException)
            : Exception(message, innerException)
        {}

        virtual ~ResourceException()
        {}
    };
}
