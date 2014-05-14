
Описание процедуры использования
библиотеки «Оплата в один клик»

Перейти к разделу:

» Алгоритм

» Инициализация

» Платеж

» Получение списка карт

» Удаление карты

» Установка карты по умолчанию

» Получение истории транзакций

» Добавление карты

» Ошибки

» Call-back URL

» Версии для загрузки

Библиотека «Оплата в один клик» для Android OS (далее просто библиотека) разработана на языке Java и представляет собой один jar файл, который содержит в себе инструменты, обеспечивающие взаимодействие с предоставляемым сервисом. Для разработки приложения, работающего с сервисом, необходимо подключить jar файл к проекту. В файле AndroidManifest.xml необходимо добавить следующие разрешения: android.permission.INTERNET;
Пример описания обрабатывающей activity в файлеAndroidManifest.xml:

<activity android:name="YourActivity"
        android:label="@string/your_activity_name">
    <intent-filter>
        <action android:name="android.intent.action.MAIN"/>
        <category android:name="android.intent.category.LAUNCHER"/>
    </intent-filter>
    <activity android:name="ua.privatbank.payoneclicklib.BrowserActivity"/>
</activity>

Алгоритм
Инициализация
Пример инициализации библиотеки в активности приложения:

@Override
public void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
    /* ваш код */
    mPay = new Pay(getApplicationContext(), new Api.ApiEventListener<ua.privatbank.payoneclicklib.Api>() {
            @Override
            public void onApiStartRequest() {
                  /* ваш код обработки начала отправки очереди запросов*/
            }

            @Override
            public void onApiFinishRequest() {
                 /* ваш код обработки завершения отправки очереди запросов */
            }

            @Override
            public void onApiError(ua.privatbank.payoneclicklib.Api api, Message.ErrorCode code) {
                  /* ваш код обработки ошибок которые приходят от сервера (список есть ниже)*/
                  /* код ошибки нужно получать этим методом: api.getLastServerFailCode() */
            }
        }, mMerchId);

    /* ваш код */
}
        

Параметры конструктора Pay:

    Context context— контект андроид приложения;
    String mMerchId— ИД мерчанта;
    Api.ApiEventListener<ua.privatbank.payoneclicklib.Api> apiEventListener— обработчик отправки запроса.

Платеж
Пример:

private void pay(PayData payData){
        try {
            mPay.pay(payData, new Pay.PaymentCallBack() {
                @Override
                public void onPaymentSuccess() {
                          /* ваш код обработки успешных платежей без  проверки  отп  */
                }

                @Override
                public void onReceiveOtpSend(Pay.OtpCheckListener otpListener) {
	           /* будет вызван когда отп пароль будет отправлен на указанный телефон*/
                             otpListener.onOtpCheck(phone, otpCode, new Pay.OtpCallBack() {
               	      @Override
                                      public void onOtpSuccess() {
                                               /*  будет вызван если отп верный*/
 		       }

                                      @Override
                                      public void onOtpFailed() {
  	                          /*  будет вызван если отп не верный */
                                       }
            		});
                }
                @Override
                public void onPaymentFailed() {
	            /* ваш код обработки ошибок при осуществлении платежа*/
                }


                @Override
                public void onPaymentProcessing() {
	          /*  ваш код обработки ошибки когда платеж находится в обработке */
                }
            });
        } catch (Exception e) {
                e.printStackTrace(
        }
    }
                    

Параметры метода pay:

    PayData payData - обьект который несет информацию о транзакции.

Инициализация обьекта:

PayData payData = new PayData();

Пример обязательно заполненных полей этого обьекта:

    payData.setCcy("UAH");
    payData.setAmount("0.01");
    payData.setDescription("test");

Пример всех остальных полей которые могут использоваться при осуществлении платежа:

    payData.setPhone(phone);
    payData.setCardId(cardId);
    payData.setNeedCvv2Flag(true);
    payData.setNeed3DSFlag(true);
    payData.setNeedOtpFlag(true);

Pay.PaymentCallBack callback - обработчик процесса оплаты.
Получение списка карт
Пример:

private void getCardList(){
        try {
            mPay.getCards(new Pay.CardListCallBack() {
                @Override
                public void onGetCardListSuccess(List<Card> cardList) {
 	          /*  ваш код обработки полученого списка карт*/
                }

                @Override
                public void onGetCardListFailed() {
  	          /*  ваш код обработки ошибок при получении списка карт */
                }
            });
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

                    

Удаление карты
Пример:

private void delCard(String cardId){
        try {
            mPay.delCard(cardId, new Pay.DelCardCallBack() {
                @Override
                public void onDelCardSuccess() {
                        /*  ваш код обработки успешного удаления карты*/
                }

                @Override
                public void onDelCardFailed() {
                        /*  ваш код обработки ошибок при удалении карты*/
                }
            });
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
                    

Установка карты по умолчанию
Пример:

private void setDefCard(String cardId){
        try {
            mPay.setDefaultCard(cardId, new Pay.SetDefaultCardCallBack() {
                @Override
                public void onSetDefCardSuccess() {
	          /* ваш код обработки успешного изменения карты по умолчанию*/
                }
                @Override
                public void onSetDefCardFailed() {
	              /* ваш код обработки ошибок при изменении карты по умолчанию*/
                }
            });
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
                    

Получение истории транзакций
Пример:

private void history(){
        try {
            mPay.getHistory(new Pay.GetHistoryCallBack() {
                @Override
                public void onGetHistorySuccess(List<Transaction> transactionList) {
	           /*  ваш код обработки полученного списка  транзакций*/
                }

                @Override
                public void onGetHistoryFailed() {
	           /* ваш код обработки ошибок при получении списка транзакций */
                }
            });
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
                    

Добавление карты
Пример:

private void addCard(String phone){
        try {
            mPay.addCard(phone, new Pay.AddCardCallBack() {

                @Override
                public void onAddCardSuccess() {
	           /*  ваш код обработки успешного добавления карты*/
                }

                @Override
                public void onReceiveOtpSend(Pay.OtpCheckListener listener) {
        	            /* будет вызван когда отп пароль будет отправлен на указанный телефон*/
                            listener.onOtpCheck(phone, otpCode, new Pay.OtpCallBack() {
                                      @Override
                                      public void onOtpSuccess() {
                                              /*  будет вызван если отп верный*/
 		      }
                                      @Override
                                       public void onOtpFailed() {
  	                               /*  будет вызван если отп не верный */
                                        }
            		});
                }

                @Override
                public void onAddCardFailed() {
        	         /*  ваш код обработки ошибок при добавлении карты */
                }

            });
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
                    

Ошибки

Ошибки по валидации данных в библиотеке:
public enum FieldException {

    amount_is_null - не указана сума платежа
    ccy_is_null - не указана валюта платежа
    description_is_null - не указано описание платежа
    phone_is_null - не указан телефон при добавлении карты
    cardId_is_null - не указан ИД карты
    callBack_is_null - не указан колбек

}
Еще ошибки
Call-back URL

В настройках своего аккаунта есть возможность указать Call-back URL. На указанный адрес устанавливается https соединение после чего оправляются данные в GET запросе.

Шаблон запроса:

https://${ХОСТ}:${ПОРТ}/${ПУТЬ}?
                id={референс платежа}
                &dt={последние 4 цифры карты, с которой проведена оплата}
                &amount={сумма платежа}
                &ccy={валюта платежа, согласно ISO}
                &description={описание покупки}
                &date={дата}
                &dt_status=approved
                &whose_card={карта ПриватБанка или нет (pb|npb)}
                &type=purchase
                &merchant_id={ваш ID мерчанта в системе}
                &sign=SHA1(id+type+date+merchant_id+whose_card+dt+amount+ccy+description+
                           dt_status+{пароль_мерчанта})

Пример запроса:

http://localhost:8008/notification?
                id=660
                &dt=5632
                &amount=559.85
                &ccy=980
                &description=оплата товара
                &date=2014-04-16 14:36:18.676395+03:00
                &dt_status=approved
                &whose_card=pb
                &type=purchase
                &merchant_id=71dd7e01597d9c17d97195e521a8b484
                &sign=aF44zTEsqbt485FJVJiamgQ6Q0s

На данный URL продавец будет извещен о покупке Если сервер продавца не отвечает, то сервер Банка будет пытаться уведомить компанию в течение следующих 24 часов с интервалом в 1 минуту
