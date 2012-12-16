package IHM;

import client.Command;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.JLabel;
import javax.swing.JFrame;

/**
 * ErrorPopup is a window that will pop-up when an error is notified to the
 * ManagementFrame and allow the user to make a choice on what to do now
 */
public class ErrorPopup extends javax.swing.JFrame
{

	/**
	 * Creates new form ErrorPopup
	 */
	public ErrorPopup()
	{
		initComponents();
	}

	/**
	 * This method is called from within the constructor to initialize the form.
	 * WARNING: Do NOT modify this code. The content of this method is always
	 * regenerated by theForm Editor.
	 */
	@SuppressWarnings("unchecked")
	// <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
	private void initComponents() {

		jB_Shutdown = new javax.swing.JButton();
		jL_WildError = new javax.swing.JLabel();
		JL_ErrorName = new javax.swing.JLabel();
		jB_RestartProd1 = new javax.swing.JButton();

		setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);

		jB_Shutdown.setBackground(new java.awt.Color(238, 0, 0));
		jB_Shutdown.setFont(new java.awt.Font("Dialog", 1, 18)); // NOI18N
		jB_Shutdown.setForeground(new java.awt.Color(255, 255, 255));
		jB_Shutdown.setText("SHUTDOWN");
		jB_Shutdown.addActionListener(new java.awt.event.ActionListener() {
			public void actionPerformed(java.awt.event.ActionEvent evt) {
				jB_ShutdownActionPerformed(evt);
			}
		});

		jL_WildError.setText("Une erreur sauvage est apparue : ");

		JL_ErrorName.setText("ERROR_NAME");

		jB_RestartProd1.setBackground(new java.awt.Color(51, 0, 255));
		jB_RestartProd1.setFont(new java.awt.Font("Dialog", 1, 18)); // NOI18N
		jB_RestartProd1.setForeground(new java.awt.Color(255, 255, 255));
		jB_RestartProd1.setText("REPRENDRE LA PRODUCTION");
		jB_RestartProd1.addActionListener(new java.awt.event.ActionListener() {
			public void actionPerformed(java.awt.event.ActionEvent evt) {
				jB_RestartProd1ActionPerformed(evt);
			}
		});

		javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
		getContentPane().setLayout(layout);
		layout.setHorizontalGroup(
			layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
			.addGroup(layout.createSequentialGroup()
				.addContainerGap()
				.addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
					.addComponent(jB_Shutdown, javax.swing.GroupLayout.PREFERRED_SIZE, 360, javax.swing.GroupLayout.PREFERRED_SIZE)
					.addGroup(layout.createSequentialGroup()
						.addGap(49, 49, 49)
						.addComponent(jL_WildError, javax.swing.GroupLayout.PREFERRED_SIZE, 254, javax.swing.GroupLayout.PREFERRED_SIZE))
					.addComponent(JL_ErrorName, javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
				.addContainerGap())
			.addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
				.addGroup(layout.createSequentialGroup()
					.addContainerGap()
					.addComponent(jB_RestartProd1, javax.swing.GroupLayout.PREFERRED_SIZE, 360, javax.swing.GroupLayout.PREFERRED_SIZE)
					.addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)))
		);
		layout.setVerticalGroup(
			layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
			.addGroup(layout.createSequentialGroup()
				.addComponent(jL_WildError, javax.swing.GroupLayout.PREFERRED_SIZE, 49, javax.swing.GroupLayout.PREFERRED_SIZE)
				.addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
				.addComponent(JL_ErrorName, javax.swing.GroupLayout.PREFERRED_SIZE, 49, javax.swing.GroupLayout.PREFERRED_SIZE)
				.addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, 128, Short.MAX_VALUE)
				.addComponent(jB_Shutdown, javax.swing.GroupLayout.PREFERRED_SIZE, 50, javax.swing.GroupLayout.PREFERRED_SIZE)
				.addContainerGap())
			.addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
				.addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
					.addContainerGap(138, Short.MAX_VALUE)
					.addComponent(jB_RestartProd1, javax.swing.GroupLayout.PREFERRED_SIZE, 94, javax.swing.GroupLayout.PREFERRED_SIZE)
					.addGap(68, 68, 68)))
		);

		pack();
	}// </editor-fold>//GEN-END:initComponents
	private ManagementFrame mgFrame;

	/**
	 * Sets the management Frame
	 *
	 * @param j management frame
	 */
	public void setMgFrame(ManagementFrame j)
	{
		this.mgFrame = j;
	}

	/**
	 * Shutdown the client application after ther server shutdown
	 *
	 * @param evt clik on shutdown button
	 */
	private void jB_ShutdownActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jB_ShutdownActionPerformed
		this.command.sendShutdown();
		try
		{
			Thread.sleep(1 * 1000);// Wait for server to shutdown...
		}
		catch (InterruptedException ex)
		{
			Logger.getLogger(ErrorPopup.class.getName()).log(Level.SEVERE, null, ex);
		}
		System.exit(0);// Shutdown the client app
	}//GEN-LAST:event_jB_ShutdownActionPerformed

	/**
	 * Restart the production
	 *
	 * @param evt click on restart button
	 */
	private void jB_RestartProd1ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jB_RestartProd1ActionPerformed
		this.command.sendRestartProd();
		this.mgFrame.setCurrentErrorState(false);
		this.mgFrame.show();
		this.hide();
	}//GEN-LAST:event_jB_RestartProd1ActionPerformed
	private Command command;

	/**
	 * Sets the command
	 *
	 * @param c command
	 */
	public void setCommand(Command c)
	{
		this.command = c;
	}

	/**
	 * Gets the ErrorName Label
	 *
	 * @return JLabel
	 */
	public JLabel getErrorNameLabel()
	{
		return this.JL_ErrorName;
	}

	/**
	 * @param args the command line arguments
	 */
	public static void main(String args[])
	{
		/* Set the Nimbus look and feel */
		//<editor-fold defaultstate="collapsed" desc=" Look and feel setting code (optional) ">
		/* If Nimbus (introduced in Java SE 6) is not available, stay with the default look and feel.
		 * For details see http://download.oracle.com/javase/tutorial/uiswing/lookandfeel/plaf.html 
		 */
		try
		{
			for (javax.swing.UIManager.LookAndFeelInfo info : javax.swing.UIManager.getInstalledLookAndFeels())
			{
				if ("Nimbus".equals(info.getName()))
				{
					javax.swing.UIManager.setLookAndFeel(info.getClassName());
					break;
				}
			}
		}
		catch (ClassNotFoundException ex)
		{
			java.util.logging.Logger.getLogger(ErrorPopup.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
		}
		catch (InstantiationException ex)
		{
			java.util.logging.Logger.getLogger(ErrorPopup.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
		}
		catch (IllegalAccessException ex)
		{
			java.util.logging.Logger.getLogger(ErrorPopup.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
		}
		catch (javax.swing.UnsupportedLookAndFeelException ex)
		{
			java.util.logging.Logger.getLogger(ErrorPopup.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
		}
		//</editor-fold>

		/* Create and display the form */
		java.awt.EventQueue.invokeLater(new Runnable()
		{
			public void run()
			{
				new ErrorPopup().setVisible(true);
			}
		});
	}
	// Variables declaration - do not modify//GEN-BEGIN:variables
	private javax.swing.JLabel JL_ErrorName;
	private javax.swing.JButton jB_RestartProd1;
	private javax.swing.JButton jB_Shutdown;
	private javax.swing.JLabel jL_WildError;
	// End of variables declaration//GEN-END:variables
}
