/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package IHM;

import client.Command;
import java.awt.Color;

/**
 *
 * @author Elodie
 */
public class NewCmdFrame extends javax.swing.JFrame {
    ManagementFrame management;
    Command threadCmd;
    
    /**
     * Creates new form NewCmdFrame
     */
    public NewCmdFrame(ManagementFrame management, Command threadCmd) {
        initComponents();
        aErrorLabel.setForeground(Color.red);
        aErrorLabel.setVisible(false);
        bErrorLabel.setForeground(Color.red);
        bErrorLabel.setVisible(false);
        this.management = management;
    }

    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        descriptionLabel = new javax.swing.JLabel();
        aLabel = new javax.swing.JLabel();
        bLabel = new javax.swing.JLabel();
        validationButton = new javax.swing.JButton();
        cancelButton = new javax.swing.JButton();
        aErrorLabel = new javax.swing.JLabel();
        bErrorLabel = new javax.swing.JLabel();
        aTextField = new javax.swing.JTextField();
        bTextField = new javax.swing.JTextField();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        setTitle("Nouvelle commande");
        setCursor(new java.awt.Cursor(java.awt.Cursor.DEFAULT_CURSOR));
        setResizable(false);
        setType(java.awt.Window.Type.POPUP);

        descriptionLabel.setText("Veuillez spécifier le nombre de palettes commandées :");

        aLabel.setText("Palettes de produits A :");

        bLabel.setText("Palettes de produits B :");

        validationButton.setText("Valider");
        validationButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                validationButtonActionPerformed(evt);
            }
        });

        cancelButton.setText("Annuler");
        cancelButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                cancelButtonActionPerformed(evt);
            }
        });

        aErrorLabel.setText("Produits indisponibles");

        bErrorLabel.setText("Produits indisponibles");

        aTextField.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                aTextFieldActionPerformed(evt);
            }
        });

        bTextField.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                bTextFieldActionPerformed(evt);
            }
        });

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                    .addComponent(descriptionLabel, javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(javax.swing.GroupLayout.Alignment.LEADING, layout.createSequentialGroup()
                        .addComponent(aLabel)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                        .addComponent(aTextField, javax.swing.GroupLayout.PREFERRED_SIZE, 39, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addGap(10, 10, 10)
                        .addComponent(aErrorLabel))
                    .addGroup(javax.swing.GroupLayout.Alignment.LEADING, layout.createSequentialGroup()
                        .addComponent(bLabel)
                        .addGap(10, 10, 10)
                        .addComponent(bTextField, javax.swing.GroupLayout.PREFERRED_SIZE, 39, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                        .addComponent(bErrorLabel))
                    .addGroup(layout.createSequentialGroup()
                        .addComponent(validationButton)
                        .addGap(18, 18, 18)
                        .addComponent(cancelButton)))
                .addContainerGap(105, Short.MAX_VALUE))
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addComponent(descriptionLabel)
                .addGap(18, 18, 18)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(aLabel)
                    .addComponent(aErrorLabel)
                    .addComponent(aTextField, javax.swing.GroupLayout.PREFERRED_SIZE, 24, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addGap(23, 23, 23)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(bLabel)
                    .addComponent(bErrorLabel)
                    .addComponent(bTextField, javax.swing.GroupLayout.PREFERRED_SIZE, 24, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addGap(19, 19, 19)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(validationButton)
                    .addComponent(cancelButton))
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void cancelButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_cancelButtonActionPerformed
        this.dispose();
    }//GEN-LAST:event_cancelButtonActionPerformed

    private void validationButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_validationButtonActionPerformed
        Boolean correct = true;
        Boolean dispo = true;
        int nbA;
        int nbB;
        
        try 
        {
            nbA = Integer.parseInt(aTextField.getText());
        }
        catch (NumberFormatException e)
        {       
            aErrorLabel.setVisible(true);
            aErrorLabel.setText("Donnée invalide");
            correct = false;
        }
        
        try 
        {
            nbB = Integer.parseInt(bTextField.getText());
        }
        catch (NumberFormatException e)
        {
            correct = false;
            bErrorLabel.setText("Donnée invalide");
            bErrorLabel.setVisible(true);
        }
        
        if (correct == true)
        {
            nbA = Integer.parseInt(aTextField.getText());
            nbB = Integer.parseInt(bTextField.getText());

            int aWarehouse = management.getPalA();
            int bWarehouse = management.getPalB();
            
            //vérification que les palettes demandées sont dipo
            if (nbA > aWarehouse)
            {
                dispo=false;
                aErrorLabel.setText("Disponibilité : " + aWarehouse);
                aErrorLabel.setVisible(true);
            }
            if (nbB > bWarehouse)
            {
                dispo=false;
                aErrorLabel.setText("Disponibilité : " + bWarehouse);
                aErrorLabel.setVisible(true);
            }
            if (dispo == true)
            {
                //envoie message au serveur pour décrémenter le stock
                threadCmd.sendCommand(nbA, nbB);

                //fermeture fenêtre
                this.dispose();

                //ouverture fenêtre de confirmation
                //TODO
            }
        }
    }//GEN-LAST:event_validationButtonActionPerformed

    private void aTextFieldActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_aTextFieldActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_aTextFieldActionPerformed

    private void bTextFieldActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_bTextFieldActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_bTextFieldActionPerformed

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JLabel aErrorLabel;
    private javax.swing.JLabel aLabel;
    private javax.swing.JTextField aTextField;
    private javax.swing.JLabel bErrorLabel;
    private javax.swing.JLabel bLabel;
    private javax.swing.JTextField bTextField;
    private javax.swing.JButton cancelButton;
    private javax.swing.JLabel descriptionLabel;
    private javax.swing.JButton validationButton;
    // End of variables declaration//GEN-END:variables
}
