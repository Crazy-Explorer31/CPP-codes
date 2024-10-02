dTdt = c()
TT = c(90, 89.2, 88.5, 87.8, 87.2, 86.8, 86.2, 85.7, 85.3, 84.8, 
       84.5, 84.1, 83.7, 83.3, 83, 82.7, 82.3, 82, 81.7, 
       81.4, 81.1, 80.7, 80.5, 80.2, 79.9, 79.6, 79.4, 79.2, 
       78.9, 78.7, 78.5)
(times = seq(0, length = length(TT), by = (2/3)))
data1 = data.frame(times = times, TT = TT)
data2 = data.frame(dTdt = dTdt, TT = TT[2:(length(TT) - 1)])



temp_data = data.frame(TT = c(23.5), dTdt = c(0))
new_data_vital <- rbind(data_for_vital, temp_data)
library(ggplot2)
ggplot(data1, aes(x = times, y = TT))+
  geom_point()+
  geom_smooth(se = F, size = 1)

ggplot(new_data_vital, aes(x = TT, y = dTdt))+
  geom_point()+
  geom_smooth(method = lm, se = F, size = 1)
model = lm(y ~ x, data)
summary(model)
library('writexl')
write_xlsx(data, 'C:\\Users\\stepa\\Documents\\data_for_vital.xlsx')
