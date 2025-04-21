#include <Novice.h>
#include <cmath>

const char kWindowTitle[] = "LE2D_02_アオヤギ_ガクト_確認課題";

struct Vector3 {
    float x, y, z;
};

struct Matrix4x4 {
    float m[4][4];
};

Matrix4x4 MakeTranslateMatrix(const Vector3& translate)
{
    Matrix4x4 matrix = {};
    matrix.m[0][0] = 1.0f;
    matrix.m[1][1] = 1.0f;
    matrix.m[2][2] = 1.0f;
    matrix.m[3][3] = 1.0f;
    matrix.m[3][0] = translate.x;
    matrix.m[3][1] = translate.y;
    matrix.m[3][2] = translate.z;
    return matrix;
}

Matrix4x4 MakeScaleMatrix(const Vector3& scale)
{
    Matrix4x4 matrix = {};
    matrix.m[0][0] = scale.x;
    matrix.m[1][1] = scale.y;
    matrix.m[2][2] = scale.z;
    matrix.m[3][3] = 1.0f;
    return matrix;
}

Vector3 Transform(const Vector3& point, const Matrix4x4& matrix)
{
    Vector3 result;
    result.x = point.x * matrix.m[0][0] + point.y * matrix.m[1][0] + point.z * matrix.m[2][0] + matrix.m[3][0];
    result.y = point.x * matrix.m[0][1] + point.y * matrix.m[1][1] + point.z * matrix.m[2][1] + matrix.m[3][1];
    result.z = point.x * matrix.m[0][2] + point.y * matrix.m[1][2] + point.z * matrix.m[2][2] + matrix.m[3][2];
    return result;
}

static const int kColumnWidth = 60;
static const int kRowHeight = 20;

void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label)
{
    Novice::ScreenPrintf(x, y, "%.02f", vector.x);
    Novice::ScreenPrintf(x + kColumnWidth, y, "%.02f", vector.y);
    Novice::ScreenPrintf(x + kColumnWidth * 2, y, "%.02f", vector.z);
    Novice::ScreenPrintf(x + kColumnWidth * 3, y, "%s", label);
};

void MatrixScreenPrintf(int x, int y, const Matrix4x4& m, const char* format)
{
    Novice::ScreenPrintf(x, y, "%s", format);
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            Novice::ScreenPrintf(x + j * kColumnWidth, y + i * kRowHeight + 20, "%6.02f",
                m.m[i][j]);
        }
    }
}

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{

    // ライブラリの初期化
    Novice::Initialize(kWindowTitle, 1280, 720);

    // キー入力結果を受け取る箱
    char keys[256] = { 0 };
    char preKeys[256] = { 0 };

    Vector3 translate = { 4.1f, 2.6f, 0.8f };
    Vector3 scale = { 1.5f, 5.2f, 7.3f };
    Matrix4x4 translateMatrix = MakeTranslateMatrix(translate);
    Matrix4x4 scaleMatrix = MakeScaleMatrix(scale);
    Vector3 point = { 2.3f, 3.8f, 1.4f };
    Matrix4x4 transformMatrix = {
        1.0f, 2.0f, 3.0f, 4.0f,
        3.0f, 1.0f, 1.0f, 2.0f,
        1.0f, 4.0f, 2.0f, 3.0f,
        2.0f, 2.0f, 1.0f, 3.0f
    };

    Vector3 transformed = Transform(point, transformMatrix);

    // ウィンドウの×ボタンが押されるまでループ
    while (Novice::ProcessMessage() == 0) {
        // フレームの開始
        Novice::BeginFrame();

        // キー入力を受け取る
        memcpy(preKeys, keys, 256);
        Novice::GetHitKeyStateAll(keys);

        ///
        /// ↓更新処理ここから
        ///

        ///
        /// ↑更新処理ここまで
        ///

        ///
        /// ↓描画処理ここから
        ///

        VectorScreenPrintf(0, 0, transformed, "transformed");
        MatrixScreenPrintf(0, kRowHeight, translateMatrix, "TranslateMatrix");
        MatrixScreenPrintf(0, kRowHeight * 6, scaleMatrix, "scaleMatrix");

        ///
        /// ↑描画処理ここまで
        ///

        // フレームの終了
        Novice::EndFrame();

        // ESCキーが押されたらループを抜ける
        if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
            break;
        }
    }

    // ライブラリの終了
    Novice::Finalize();
    return 0;
}
