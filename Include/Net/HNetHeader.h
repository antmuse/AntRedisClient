#ifndef APP_CNETHEADER_H
#define APP_CNETHEADER_H

#include "HConfig.h"
#include "irrTypes.h"


namespace irr {
namespace net {

#pragma pack(1)

struct SHeadIP {
    enum EFlag {
        EFLAG_MORE_FRAG = 0x1,  //more fragment
        EFLAG_NO_FRAG = 0x2,    //don't fragment
        EFLAG_R = 0x4,          //abandon
    };
    //@see SHeadIP::mProtocol
    enum EProtocalType {
        EPT_ICMP = 1,
        EPT_TCP = 6,
        EPT_UDP = 17
    };
    u8  mVerAndSize;        // ��λIP�汾�ţ���λ�ײ�����
    u8  mType;              // ��������
    u16 mTotalSize;         // �ܵ����ݰ�����
    u16 mIdent;             // �����ʶ��
    u16 mFlag;              // 3λ��־λ,13λƬλ��
    u8  mTTL;               // ����ʱ��
    u8  mProtocol;          // Э�飨TCP��UDP�ȣ�
    u16 mChecksum;          // IPУ���=ipͷ��
    u32 mLocalIP;           // Դ��ַ
    u32 mRemoteIP;          // Ŀ���ַ

    //3bit flags
    APP_INLINE void setFlag(u16 it) {
#if defined(APP_ENDIAN_BIG)
        mFlag = (mFlag & 0x1FFF) | (it << 13);
#else
        mFlag = (mFlag & 0xFF1F) | ((it & 0x0007) << 5);//bug clean
#endif
    }

    APP_INLINE u16 getFlag()const {
#if defined(APP_ENDIAN_BIG)
        return (mFlag & 0xE000) >> 13;
#else
        return (mFlag & 0x000E) >> 5;
#endif
    }

    //Get ident, in OS endian.
    APP_INLINE u16 getIdent()const {
#if defined(APP_ENDIAN_BIG)
        return mIdent;
#else
        return APP_SWAP16(mIdent);
#endif
    }


    APP_INLINE void setIdent(u16 it) {
#if defined(APP_ENDIAN_BIG)
        mIdent = it;
#else
        mIdent = APP_SWAP16(it);
#endif
    }


    APP_INLINE void setTotalSize(u16 it) {
#if defined(APP_ENDIAN_BIG)
        mTotalSize = it;
#else
        mTotalSize = APP_SWAP16(it);
#endif
    }

    //Get total size, in OS endian.
    APP_INLINE u16 getTotalSize()const {
#if defined(APP_ENDIAN_BIG)
        return mTotalSize;
#else
        return APP_SWAP16(mTotalSize);
#endif
    }

    APP_INLINE void setVersion(u8 it) {
#if defined(APP_ENDIAN_BIG)
        mVerAndSize = (mVerAndSize & 0xF0) | (it & 0x0F);
#else
        mVerAndSize = (mVerAndSize & 0x0F) | (it << 4);
#endif
    }

    APP_INLINE u8 getVersion()const {
#if defined(APP_ENDIAN_BIG)
        return (mVerAndSize & 0x0F);
#else
        return (mVerAndSize & 0xF0) >> 4;
#endif
    }

    APP_INLINE void setSize(u8 it) {
        it >>= 2; // it/=sizeof(u32);  it/=4;
#if defined(APP_ENDIAN_BIG)
        mVerAndSize = (mVerAndSize & 0x0F) | (it << 4);
#else
        mVerAndSize = (mVerAndSize & 0xF0) | (it & 0x0F);
#endif
    }

    APP_INLINE u8 getSize()const {
#if defined(APP_ENDIAN_BIG)
        //return (mVerAndSize & 0xF0) >> 4;
        return (mVerAndSize & 0xF0) >> 2; //it*=4;
#else
        return (mVerAndSize & 0x0F) << 2; //it*=4;
#endif
    }
};

struct SHeadICMP {
    u8  mType;                  //ICMP����ͷ
    u8  mCode;                  //ICMP����
    u16 mChecksum;             //�����=ICMPͷ+����
    u16 mID;                   //��ʶ��
    u16 mSN;                   //���к�
    u32 mTimestamp;            //ʱ���
};

struct SHeadOptionIP {
    u8 mType;           // ѡ������
    u8 mSize;           //ѡ��ͷ�ĳ���
    u8 mOffset;         //��ַƫ���� 
    u32 mAddress[9];    // IP��ַ�б�
};

struct SFakeHeadTCP {
    u32 mLocalIP;        //Դ��ַ
    u32 mRemoteIP;       //Ŀ�ĵ�ַ
    u8  mPadding;        //���λ��ȡ0
    u8  mProtocol;       //Э������
    u16 mSizeofTCP;      //����TCP����=SHeadTCP+SHeadOptionTCP+data(�����), ������SFakeHeadTCP��

    APP_INLINE void setSize(u16 it) {
#if defined(APP_ENDIAN_BIG)
        mSizeofTCP = it;
#else
        mSizeofTCP = APP_SWAP16(it);
#endif
    }
};

struct SHeadTCP {
    enum EFlag {
        EFLAG_URG = 0x20,   //������־���ͽ���ָ�����ʹ�ã�����Ϊ1ʱ��ʾ���˱���Ҫ���촫�͡�
        EFLAG_ACK = 0x10,   //ȷ�ϱ�־����ȷ�Ϻ��ֶ����ʹ�ã���ACKλ��1ʱ��ȷ�Ϻ��ֶ���Ч��
        EFLAG_PSH = 0x08,   //Ϊ���ͱ�־����1ʱ�����ͷ����������ͻ������е����ݡ�
        EFLAG_RST = 0x04,   //��λ��־����1ʱ�����������ز�������ͷ����ӡ�
        EFLAG_SYN = 0x02,   //ͬ����־����1ʱ����ʾ���������ӡ�
        EFLAG_FIN = 0x01    //��ֹ��־����1ʱ�����������Ѿ������꣬�����ͷ����ӡ�
    };
    u16 mLocalPort;          //16λԴ�˿�
    u16 mRemotePort;         //16λĿ�Ķ˿�
    u32 mSN;                 //32λ���к�
    u32 mACK;                //32λȷ�Ϻ�
    u16 mSizeReserveFlag;    //4λTCPͷ����,6λ����λ,6λ��־λ
    u16 mWindow;             //16λ���ڴ�С
    u16 mChecksum;           //16λУ���=tcpαͷ��+tcpͷ��+data(�����)
    u16 mOffset;             //16λ��������ƫ����

    //Get SN, in OS endian.
    APP_INLINE u32 getSN() const {
#if defined(APP_ENDIAN_BIG)
        return mSN;
#else
        return APP_SWAP32(mSN);
#endif
    }

    APP_INLINE void setSN(u32 it) {
#if defined(APP_ENDIAN_BIG)
        mSN = it;
#else
        mSN = APP_SWAP32(it);
#endif
    }

    APP_INLINE void setACK(u32 it) {
#if defined(APP_ENDIAN_BIG)
        mACK = it;
#else
        mACK = APP_SWAP32(it);
#endif
    }

    //Get ACK, in OS endian.
    APP_INLINE u32 getACK()const {
#if defined(APP_ENDIAN_BIG)
        return mACK;
#else
        return APP_SWAP32(mACK);
#endif
    }

    //Get local port, in OS endian.
    APP_INLINE u16 getLocalPort()const {
#if defined(APP_ENDIAN_BIG)
        return mLocalPort;
#else
        return APP_SWAP16(mLocalPort);
#endif
    }

    //Get remote port, in OS endian.
    APP_INLINE u16 getRemotePort()const {
#if defined(APP_ENDIAN_BIG)
        return mRemotePort;
#else
        return APP_SWAP16(mRemotePort);
#endif
    }

    APP_INLINE void setWindowSize(u16 it) {
#if defined(APP_ENDIAN_BIG)
        mWindow = it;
#else
        mWindow = APP_SWAP16(it);
#endif
    }

    //Get window size, in OS endian.
    APP_INLINE u16 getWindowSize() const {
#if defined(APP_ENDIAN_BIG)
        return mWindow;
#else
        return APP_SWAP16(mWindow);
#endif
    }

    APP_INLINE void setSize(u16 it) {
        it >>= 2; // it/=sizeof(u32);  it/=4;
#if defined(APP_ENDIAN_BIG)
        mSizeReserveFlag = (mSizeReserveFlag & 0x0FFF) | (it << 12);
#else
        mSizeReserveFlag = (mSizeReserveFlag & 0xFF0F) | ((it & 0x000F) << 4);//bug clean
#endif
    }

    APP_INLINE u8 getSize()const {
#if defined(APP_ENDIAN_BIG)
        return ((mSizeReserveFlag & 0xF000) >> 10);   //it*=4;
#else
        return (mSizeReserveFlag & 0x00F0) >> 2; //it*=4;
#endif
    }

    APP_INLINE void setFlag(u16 it) {
#if defined(APP_ENDIAN_BIG)
        mSizeReserveFlag = (mSizeReserveFlag & 0xFFC0) | (it & 0x003F);
#else
        mSizeReserveFlag = (mSizeReserveFlag & 0xC0FF) | ((it & 0x003F) << 8); //bug clean
#endif
    }

    APP_INLINE u8 getFlag()const {
#if defined(APP_ENDIAN_BIG)
        return (mSizeReserveFlag & 0x003F);
#else
        return (mSizeReserveFlag & 0x3F00) >> 8;//bug clean
#endif
    }
};

struct SHeadOptionTCP {
    enum EType {
        ETYPE_OPTION_END = 0x0,     //option end
        ETYPE_NO_OPTION = 0x1,      //No option
        ETYPE_MSS = 0x2,            //MSS
        ETYPE_WIN_SCALE = 0x3,      //Window enlarge rate
        ETYPE_SACK_PERMITTED = 0x4,   //SACK permitted
        ETYPE_TIMESTAMP = 0x8,      //Timestamp
    };
    u8 mType;           //ѡ������
    u8 mSize;           //ѡ��ͷ�ĳ���
    u16 mMSS;           //MSS
    u8 mOther[8];       //Other options

    APP_INLINE void setMSS(u16 it) {
#if defined(APP_ENDIAN_BIG)
        mMSS = it;
#else
        mMSS = APP_SWAP16(it);
#endif
    }

};

struct SHeadUDP {
    u16 mLocalPort;       // Source port
    u16 mRemotePort;      // Destination port
    u16 mSize;            // Datagram length
    u16 mChecksum;        // Checksum
};

//14bytes
struct SHeadEthernet {
    u8  mRemoteMAC[6];          //Ŀ��MAC��ַ
    u8  mLocalMAC[6];           //ԴMAC��ַ
    u16 mType;                  //��һ��Э�����ͣ���0x0800������һ����IPЭ�飬0x0806Ϊarp
};

//28bytes
struct SHeadARP {
    u16 mHardwareType;      //Ӳ������,2�ֽڣ���������ARP����������ͣ���̫��������1
    u16 mProtocol;          //Э������,2�ֽڣ������ϲ�Э�����ͣ�����IPV4Э�飬���ֶ�ֵΪ0800
    u8 mHardwareAddressLen; //Ӳ����ַ����,8λ�ֶΣ������Ӧ�����ַ���ȣ���̫�������ֵΪ6
    u8 mProtocolAddressLen; //Э���ַ����,8λ�ֶΣ��������ֽ�Ϊ��λ���߼���ַ���ȣ���IPV4Э�����ֵΪ4
    u16 mOperation;            //�����ֶ�,���ݰ�����,ARP����ֵΪ1��������ARPӦ��ֵΪ2��
    u8 mLocalMAC[6];           //Դ�����Ͷˣ�mac��ַ,�ɱ䳤���ֶΣ�����̫������ֶ���6�ֽڳ�
    u8 mLocalIP[4];            //Դ�����Ͷ̣�ip��ַ,���Ͷ�Э���ַ���ɱ䳤���ֶΣ���IPЭ�飬����ֶ���4�ֽڳ�
    u8 mRemoteMAC[6];          //Ŀ�ģ����նˣ�mac��ַ
    u8 mRemoteIP[4];           //Ŀ�ģ����նˣ�ip��ַ,ע�ⲻ��Ϊu_int�ͣ��ṹ�����
};


struct SNetPackARP {
    SHeadEthernet mEthernet;
    SHeadARP mARP;
};

#pragma pack()

}//namespace net
}//namespace irr

#endif //APP_CNETHEADER_H
