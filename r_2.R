TT <- c(90, 89, 88.5, 88, 87.5, 87, 86, 86, 85.5, 85,
        84.5, 84.5, 84, 83.5, 83, 83, 82.5, 82, 82, 81.5, 81, 81,
        80.5, 80, 80, 80, 79.5, 79, 79, 79, 78.5)
(t <- seq(0, length = 31, by = (1/3)))
plot(t, TT)
data = data.frame(t = t, TT = TT)
library(ggplot2)
ggplot(data, aes(x = t, y = TT))+
  geom_point()+
  geom_smooth(se = F, size = 1)

dTdt = c(2.25, 1.5, 1.5, 2.25, 2.25, 1.5, 0.75, 0.75, 1.5, 0.75,
         0.75, 1.5, 1.5, 0.75, 0.75, 1.5, 0.75, 0.75, 1.5, 0.75,
         0.75, 1.5, 0.75, 0.0, 0.75, 1.5, 0.75, 0.0, 0.75)
new_data <- data.frame(TT_new = TT[2:(length(TT) - 1)], dTdt = dTdt)
ggplot(new_data, aes(x = TT_new, y = dTdt))+
  geom_point()+
  geom_smooth(method = lm, se = F, size = 1)

model <- lm(dTdt ~ TT_new, new_data)
summary(model)

library('writexl')
write_xlsx(new_data, 'C:\\Users\\stepa\\Documents\\new_data.xlsx')
