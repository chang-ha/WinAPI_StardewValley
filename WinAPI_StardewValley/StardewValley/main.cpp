// ������ ���α׷��� ��������� ���� ���� (exe���ϻ��� ������Ʈ�� �ش�)
// ������Ʈ ���� << ��Ŀ << �ý��� << ���� �ý���(�ܼ� -> â)

// ���� ��� ��ġ �ٲٴ� ����
// ������Ʈ ���� << ��� ���丮 or �߰� ���丮 << �Ʒ� ȭ��ǥ ������ �������� ���ϴ� ��η� ����

// ���Ӽ� ����
// �ַ�� ������Ʈ ���� << ���Ӽ� ���� << ���� ���� Level�� �� ���Ӽ� üũ �������

// ���� ���μ��� ������
// ������Ʈ ���� << C/C++ << �Ϲ� << �Ʒ��� ���� ���μ��� ������
// ��Ƽ�ھ� ����ؼ� �������ִ� �ɼ�

// �� �������� �𸣸� �ش� �ܰ踦 ���󰡾���(����� �Ǿ��� ��, ������ ���� x)
// �׷��� Bin �ѹ� ����� �ٽ� �����غ��� << 100�� 99�� �� �߸��� (���� ���� vs���׷� ���� �׷� �� ������ �õ��� �غ���)

#include <GameEngineCore/GameEngineCore.h>


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    // �����ʿ��� �������� ���ؼ� �����̵� �˸� �ȵ� (�𸮾������� �÷��̾ �˾ƾ� �Ѵٴ� �Ҹ���)
    // �׷��� �츮�� �� ��(�Լ�)�� �����쿡 �Ѱ��ָ� �����찡 �� ���� ��� ó������
    // �̷��� ����� "Call Back" ����̶�� �Ѵ�.
    // GameEngineWindow::MessageLoop(hInstance, TestStart, TestUpdate, TestEnd);
    // GameEngineWindow::MessageLoop(hInstance, nullptr, nullptr, nullptr);
    GameEngineCore::EngineStart("StardewValley", hInstance);
    return 0;
}
