#pragma once

#include "../ControlOfDX.h"
#include "../SingletonFactory.h"
#include "VisualResource.h"
#include "VisualResourceOfSolidColorBrush.h"
#include "VisualResourceOfPathGeometry.h"
#include "VisualResourceOfBitmap.h"
#include "VisualResourceOfBitmapBrush.h"
#include "VisualResourceOfD2BitmapBrush.h"
#include "VisualResourceOfLineGradientBrush.h"
#include "VisualResourceOfRadialGradientBrush.h"
#include "VisualResourceOfTextFormat.h"
#include "VisualResourceOfStrokeStyle.h"
#include "VisualResourceOfEllipseGeometry.h"
#include "VisualResourceOfRectangleGeometry.h"
#include "VisualResourceOfTransformedGeometry.h"

namespace ControlOfDX
{
    using namespace System;
    using namespace System::Collections::Generic;

    /// <summary>���\�[�X�E�R���N�V�����B</summary>
	public ref class VisualResources sealed
	{
#pragma region "fields"
    private:
        /// <summary>���\�[�X�E�e�[�u���B</summary>
        SortedDictionary<String ^, VisualResource ^>^ items;

#pragma endregion

#pragma region "properties"
    public:
        /// <summary>�o�^���Ă��郊�\�[�X�����擾����B</summary>
        /// <return>���\�[�X���B</return>
        property int Count
        {
            int get() {
                return this->items->Count;
            }
        }

        /// <summary>���O���w�肵�ă��\�[�X���擾����B</summary>
        /// <param name="name">���\�[�X���B</param>
        /// <return>���\�[�X�B</return>
        property VisualResource ^ default[String^]
        {
            VisualResource ^ get(String^ name) {
                VisualResource ^ val;
                return (this->items->TryGetValue(name, val) ? val : nullptr);
            }
        }

        /// <summary>���\�[�X����񋓂���B</summary>
        property SortedDictionary<String ^, VisualResource ^>::KeyCollection ^ Keys
        {
            SortedDictionary<String ^, VisualResource ^>::KeyCollection ^ get() {
                return this->items->Keys;
            }
        }

        /// <summary>���\�[�X��񋓂���B</summary>
        property SortedDictionary<String ^, VisualResource ^>::ValueCollection ^ Values
        {
            SortedDictionary<String ^, VisualResource ^>::ValueCollection ^ get() {
                return this->items->Values;
            }
        }

#pragma endregion

#pragma region "constructor/destructor"
	public:
        /// <summary>�R���X�g���N�^�B</summary>
        VisualResources()
        {
            this->items = gcnew SortedDictionary<String ^, VisualResource ^>();
        }

#pragma endregion

#pragma region "methods"
	public:
        /// <summary>�S�Ẵ��\�[�X���폜����B</summary>
        void Clear()
        {
            this->items->Clear();
        }

        /// <summary>�w�薼�̃��\�[�X��ێ����Ă�����^��Ԃ��B</summary>
        /// <param name="name">���\�[�X���B</param>
        /// <return>���\�[�X�������Ă�����^�B</return>
        bool HasResource(String^ name)
        {
            return this->items->ContainsKey(name);
        }

        /// <summary>�w�薼�̃��\�[�X���폜����B</summary>
        /// <param name="name">�폜���郊�\�[�X���B</param>
        void Remove(String ^ name)
        {
            if (this->items->ContainsKey(name)) {
                delete this->items[name];
                this->items->Remove(name);
            }
        }

    private:
        /// <summary>���\�[�X��ǉ�����B</summary>
        /// <param name="name">���\�[�X���B</param>
        /// <param name="resource">�ǉ����郊�\�[�X�B</param>
        void Add(String ^ name, VisualResource ^ resource)
        {
            this->items->Add(name, resource);
        }

    public:
        //-------------------------------------------------------------------------
        // ���\�[�X�쐬
        //-------------------------------------------------------------------------
        /// <summary>�\���b�h�J���[�u���V���쐬����B</summary>
        /// <param name="name">���\�[�X���B</param>
        /// <param name="red">�ԐF�����B</param>
        /// <param name="green">�ΐF�����B</param>
        /// <param name="blue">�F�����B</param>
        /// <param name="alpha">���������B</param>
        /// <return>���\�[�X�B</return>
        VisualResourceOfSolidColorBrush ^ CreateSolidColorBrush(String ^ name, int red, int green, int blue, int alpha)
        {
            VisualResourceOfSolidColorBrush ^ res = gcnew VisualResourceOfSolidColorBrush(name, red, green, blue, alpha);
            this->items->Add(res->Name, res);
            return res;
        }

        /// <summary>�\���b�h�J���[�u���V���쐬����B</summary>
        /// <param name="name">���\�[�X���B</param>
        /// <param name="color">�u���V�̐F�B</param>
        /// <return>���\�[�X�B</return>
        VisualResourceOfSolidColorBrush ^ CreateSolidColorBrush(String ^ name, Color color)
        {
            VisualResourceOfSolidColorBrush ^ res = gcnew VisualResourceOfSolidColorBrush(name, color.R, color.G, color.B, color.A);
            this->items->Add(res->Name, res);
            return res;
        }

        /// <summary>�W�I���g�����쐬����B</summary>
        /// <param name="name">���\�[�X���B</param>
        /// <return>���\�[�X�B</return>
        VisualResourceOfPathGeometry ^ CreatePathGeometry(String ^ name)
        {
            VisualResourceOfPathGeometry ^ res = gcnew VisualResourceOfPathGeometry(name);
            this->items->Add(res->Name, res);
            return res;
        }

        /// <summary>�~�`�W�I���g�����쐬����B</summary>
        /// <param name="name">���\�[�X���B</param>
        /// <param name="ellipse">�ȉ~���B</param>
        /// <return>���\�[�X�B</return>
        VisualResourceOfEllipseGeometry ^ CreateEllipseGeometry(String ^ name, Ellipse ellipse)
        {
            VisualResourceOfEllipseGeometry ^ res = gcnew VisualResourceOfEllipseGeometry(name, ellipse);
            this->items->Add(res->Name, res);
            return res;
        }

        /// <summary>�~�`�W�I���g�����쐬����B</summary>
        /// <param name="name">���\�[�X���B</param>
        /// <param name="center">���S�ʒu�B</param>
        /// <param name = "radiusX">�ȉ~ X���a�B< / param>
        /// <param name = "radiusY">�ȉ~ Y���a�B< / param>
        /// <return>���\�[�X�B</return>
        VisualResourceOfEllipseGeometry ^ CreateEllipseGeometry(String ^ name, PointF center, float radiusX, float radiusY)
        {
            VisualResourceOfEllipseGeometry ^ res = gcnew VisualResourceOfEllipseGeometry(name, center, radiusX, radiusY);
            this->items->Add(res->Name, res);
            return res;
        }

        /// <summary>�r�b�g�}�b�v���쐬����B</summary>
        /// <param name="name">���\�[�X���B</param>
        /// <param name="bitmap">���Ƃ����r�b�g�}�b�v�B</param>
        /// <return>���\�[�X�B</return>
        VisualResourceOfBitmap ^ CreateBitmap(String ^ name, Bitmap ^ bitmap)
        {
            VisualResourceOfBitmap ^ res = gcnew VisualResourceOfBitmap(name, bitmap);
            this->items->Add(res->Name, res);
            return res;
        }

        /// <summary>�r�b�g�}�b�v�u���V���쐬����B</summary>
        /// <param name="name">���\�[�X���B</param>
        /// <param name="bitmap">�u���V�Ɏg�p����r�b�g�}�b�v�B</param>
        /// <return>���\�[�X�B</return>
        VisualResourceOfBitmapBrush ^ CreateBitmapBrush(String ^ name, Bitmap ^ bitmap)
        {
            VisualResourceOfBitmapBrush ^ res = gcnew VisualResourceOfBitmapBrush(name, bitmap);
            this->items->Add(res->Name, res);
            return res;
        }

        /// <summary>�r�b�g�}�b�v�u���V���쐬����B</summary>
        /// <param name="name">���\�[�X���B</param>
        /// <param name="bitmap">�u���V�Ɏg�p����r�b�g�}�b�v�B</param>
        /// <return>���\�[�X�B</return>
        VisualResourceOfD2BitmapBrush ^ CreateBitmapBrush(String ^ name, VisualResourceOfBitmap ^ bitmap)
        {
            VisualResourceOfD2BitmapBrush ^ res = gcnew VisualResourceOfD2BitmapBrush(name, bitmap);
            this->items->Add(res->Name, res);
            return res;
        }

        /// <summary>���C���O���f�[�V�����u���V���쐬����B</summary>
        /// <param name="name">���\�[�X���B</param>
        /// <return>���\�[�X�B</return>
        VisualResourceOfLinearGradientBrush ^ CreateLinearGradientBrush(String ^ name)
        {
            VisualResourceOfLinearGradientBrush ^ res = gcnew VisualResourceOfLinearGradientBrush(name);
            this->items->Add(res->Name, res);
            return res;
        }

        /// <summary>���˃O���f�[�V�����u���V���쐬����B</summary>
        /// <param name="name">���\�[�X���B</param>
        /// <return>���\�[�X�B</return>
        VisualResourceOfRadialGradientBrush ^ CreateRadialGradientBrush(String ^ name)
        {
            VisualResourceOfRadialGradientBrush ^ res = gcnew VisualResourceOfRadialGradientBrush(name);
            this->items->Add(res->Name, res);
            return res;
        }

        /// <summary>�����񏑎����\�[�X���쐬����B</summary>
        /// <param name="name">���\�[�X���B</param>
        /// <return>���\�[�X�B</return>
        VisualResourceOfTextFormat ^ CreateTextFormat(String ^ name)
        {
            VisualResourceOfTextFormat ^ res = gcnew VisualResourceOfTextFormat(name);
            this->items->Add(res->Name, res);
            return res;
        }

        /// <summary>�X�g���[�N�X�^�C�����쐬����B</summary>
        /// <param name="name">���\�[�X���B</param>
        /// <return>���\�[�X�B</return>
        VisualResourceOfStrokeStyle ^ CreateStrokeStyle(String ^ name)
        {
            VisualResourceOfStrokeStyle ^ res = gcnew VisualResourceOfStrokeStyle(name);
            this->items->Add(res->Name, res);
            return res;
        }

        /// <summary>��`�W�I���g�����\�[�X���쐬����B</summary>
        /// <param name="name">���\�[�X���B</param>
        /// <param name="rectangle">�쐬�����`�B</param>
        /// <return>���\�[�X�B</return>
        VisualResourceOfRectangleGeometry ^ CreateRectangleGeometry(String ^ name, RectangleF rectangle)
        {
            VisualResourceOfRectangleGeometry ^ res = gcnew VisualResourceOfRectangleGeometry(name, rectangle);
            this->items->Add(res->Name, res);
            return res;
        }

        /// <summary>�ό`�W�I���g�����\�[�X���쐬����B</summary>
        /// <param name="name">���\�[�X���B</param>
        /// <param name="pathGeometry">�ό`����W�I���g���B</param>
        /// <param name="matrix">�ό`�}�g���N�X�B</param>
        /// <return>���\�[�X�B</return>
        VisualResourceOfTransformedGeometry ^ CreateTransformedGeometry(String ^ name,
                                                                        VisualResourceOfPathGeometry ^ pathGeometry,
                                                                        Matrix matrix)
        {
            VisualResourceOfTransformedGeometry ^ res = gcnew VisualResourceOfTransformedGeometry(name, pathGeometry, matrix);
            this->items->Add(res->Name, res);
            return res;
        }

#pragma endregion
	};
}